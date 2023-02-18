#ifndef RC_PROCESS_H_INCLUDED
#define RC_PROCESS_H_INCLUDED

#include <iostream>
#include <SDL2/SDL.h>
#include <queue>
#include "rc_matrix.h"
#include "rc_defines.h"

#define MAX_SUBPROCESS 3

#define RC_THREAD_ONERROR_CONTINUE 0
#define RC_THREAD_ONERROR_WAIT 1
#define RC_THREAD_ONERROR_STOP 2

SDL_Thread* rc_subprocess_thread[3];

struct rc_threadData
{
    uint32_t sub_process_num;
};

rc_threadData rc_subprocess_param[3];

struct rc_subprocess_mutex_container
{
    SDL_mutex* queue_mutex;
    SDL_mutex* current_op_mutex;
    SDL_mutex* error_mode_mutex;
    bool queue_mutex_locked;
    bool current_op_mutex_locked;
    bool error_mode_mutex_locked;
};

rc_subprocess_mutex_container rc_subprocess_mutex[3];


struct rc_process_op
{
    uint32_t fn;
    double n[10];
    // I will add a string arg whenever a string op gets implemented
};

struct rc_process_op_list
{
    queue<rc_process_op> op;
};

rc_process_op_list rc_subprocess_queue[3];

uint32_t rc_subprocess_error_mode[3];
int rc_subprocess_error[3];
uint32_t rc_subprocess_error_status[3];

int rc_active_matrix_process = -1;

void rc_initSubprocessSystem()
{
    for(int i = 0; i < MAX_SUBPROCESS; i++)
    {
        rc_subprocess_thread[i] = NULL;
        rc_subprocess_mutex[i].current_op_mutex = SDL_CreateMutex();
        rc_subprocess_mutex[i].error_mode_mutex = SDL_CreateMutex();
        rc_subprocess_mutex[i].queue_mutex = SDL_CreateMutex();
        rc_subprocess_mutex[i].current_op_mutex_locked = false;
        rc_subprocess_mutex[i].error_mode_mutex_locked = false;
        rc_subprocess_mutex[i].queue_mutex_locked = false;
    }
}

#define RC_QUEUE_MUTEX 1
#define RC_ERROR_MODE_MUTEX 2
#define RC_CURRENT_OP_MUTEX 3

void rc_lockMutex(uint32_t process_num, uint32_t m)
{
    switch(m)
    {
        case RC_QUEUE_MUTEX:
            if(!rc_subprocess_mutex[process_num].queue_mutex_locked)
                SDL_LockMutex(rc_subprocess_mutex[process_num].queue_mutex);
            rc_subprocess_mutex[process_num].queue_mutex_locked = true;
            break;

        case RC_ERROR_MODE_MUTEX:
            if(!rc_subprocess_mutex[process_num].error_mode_mutex_locked)
                SDL_LockMutex(rc_subprocess_mutex[process_num].error_mode_mutex);
            rc_subprocess_mutex[process_num].error_mode_mutex_locked = true;
            break;

        case RC_CURRENT_OP_MUTEX:
            if(!rc_subprocess_mutex[process_num].current_op_mutex_locked)
                SDL_LockMutex(rc_subprocess_mutex[process_num].current_op_mutex);
            rc_subprocess_mutex[process_num].current_op_mutex_locked = true;
            break;
    }
}

void rc_unlockMutex(uint32_t process_num, uint32_t m)
{
    switch(m)
    {
        case RC_QUEUE_MUTEX:
            rc_subprocess_mutex[process_num].queue_mutex_locked = false;
            SDL_UnlockMutex(rc_subprocess_mutex[process_num].queue_mutex);
            break;

        case RC_ERROR_MODE_MUTEX:
            rc_subprocess_mutex[process_num].error_mode_mutex_locked = false;
            SDL_UnlockMutex(rc_subprocess_mutex[process_num].error_mode_mutex);
            break;

        case RC_CURRENT_OP_MUTEX:
            rc_subprocess_mutex[process_num].current_op_mutex_locked = false;
            SDL_UnlockMutex(rc_subprocess_mutex[process_num].current_op_mutex);
            break;
    }
}

int rc_subprocess_fn( void* data)
{
    rc_threadData* param = (rc_threadData*) data;

    int process_num = param->sub_process_num;

    //std::cout << "thread start " << process_num << std::endl;

    rc_process_op op;
    bool p_loop = true;

    while(p_loop)
    {
        op.fn = -1;
        rc_lockMutex(process_num, RC_QUEUE_MUTEX);
        if(rc_subprocess_queue[process_num].op.size() > 0)
        {
            op = rc_subprocess_queue[process_num].op.front();
            rc_subprocess_queue[process_num].op.pop();
            rc_unlockMutex(process_num, RC_QUEUE_MUTEX);
        }
        else
            rc_unlockMutex(process_num, RC_QUEUE_MUTEX);

        rc_lockMutex(process_num, RC_CURRENT_OP_MUTEX);
        rc_lockMutex(process_num, RC_ERROR_MODE_MUTEX);

        switch(op.fn)
        {
            case 0:
                p_loop = false;
                break;

            case FN_DimMatrix: //Sub Procedure
                DimMatrix(op.n[0], op.n[1], op.n[2], op.n[3]);
            break;
            case FN_AddMatrix: //Number Function
                rc_subprocess_error[0] = (AddMatrix(op.n[0], op.n[1], op.n[2])) ? 0 : op.fn;
            break;
            case FN_AugmentMatrix: //Number Function
                rc_subprocess_error[0] = (AugmentMatrix(op.n[0], op.n[1], op.n[2])) ? 0 : op.fn;
            break;
            case FN_CopyMatrix: //Sub Procedure
                CopyMatrix(op.n[0], op.n[1]);
            break;
            case FN_InsertMatrixColumns: //Number Function
                rc_subprocess_error[0] = (InsertMatrixColumn(op.n[0], op.n[1], op.n[2])) ? 0 : op.fn;
            break;
            case FN_InsertMatrixRows: //Number Function
                rc_subprocess_error[0] = (InsertMatrixRow(op.n[0], op.n[1], op.n[2])) ? 0 : op.fn;
            break;
            case FN_MultiplyMatrix: //Number Function
                rc_subprocess_error[0] = (MultiplyMatrix(op.n[0], op.n[1], op.n[2])) ? 0 : op.fn;
            break;
            case FN_CubeMatrix: //Number Function
                rc_subprocess_error[0] = (CubeMatrix(op.n[0], op.n[1])) ? 0 : op.fn;
            break;
            case FN_DeleteMatrixColumns: //Number Function
                rc_subprocess_error[0] = (DeleteMatrixColumns(op.n[0], op.n[1], op.n[2])) ? 0 : op.fn;
            break;
            case FN_DeleteMatrixRows: //Number Function
                rc_subprocess_error[0] = (DeleteMatrixRows(op.n[0], op.n[1], op.n[2])) ? 0 : op.fn;
            break;
            case FN_ClearMatrix: //Sub Procedure
                ClearMatrix(op.n[0]);
            break;
            case FN_ClearMatrixColumns: //Number Function
                rc_subprocess_error[0] = (ClearMatrixColumns(op.n[0], op.n[1], op.n[2])) ? 0 : op.fn;
            break;
            case FN_ClearMatrixRows: //Number Function
                rc_subprocess_error[0] = (ClearMatrixRows(op.n[0], op.n[1], op.n[2])) ? 0 : op.fn;
            break;
            case FN_FillMatrix: //Sub Procedure
                FillMatrix(op.n[0], op.n[1]);
            break;
            case FN_FillMatrixColumns: //Number Function
                rc_subprocess_error[0] = (FillMatrixColumns(op.n[0], op.n[1], op.n[2], op.n[3])) ? 0 : op.fn;
            break;
            case FN_FillMatrixRows: //Number Function
                rc_subprocess_error[0] = (FillMatrixRows(op.n[0], op.n[1], op.n[2], op.n[3])) ? 0 : op.fn;
            break;
            case FN_GetMatrixColumns: //Number Function
                rc_subprocess_error[0] = (GetMatrixColumns(op.n[0], op.n[1], op.n[2], op.n[3])) ? 0 : op.fn;  // 1 needs to be replaced with error code
            break;
            case FN_GetMatrixRows: //Number Function
                rc_subprocess_error[0] = (GetMatrixRows(op.n[0], op.n[1], op.n[2], op.n[3])) ? 0 : op.fn;  // 1 needs to be replaced with error code
            break;
            case FN_IdentityMatrix: //Sub Procedure
                IdentityMatrix(op.n[0], op.n[1]);
            break;
            case FN_SolveMatrix: //Number Function
                rc_subprocess_error[0] = (SolveMatrix(op.n[0], op.n[1], op.n[2])) ? 0 : op.fn;  // 1 needs to be replaced with error code
            break;
            case FN_IsEqualMatrix: //Number Function
                rc_subprocess_error[0] = (IsEqualMatrix(op.n[0], op.n[1], op.n[2])) ? 0 : op.fn;  // 1 needs to be replaced with error code
            break;
            case FN_AdjointMatrix: //Number Function
                rc_subprocess_error[0] = (AdjointMatrix(op.n[0], op.n[1])) ? 0 : op.fn;  // 1 needs to be replaced with error code
            break;
            case FN_InvertMatrix: //Number Function
                rc_subprocess_error[0] = (InvertMatrix(op.n[0], op.n[1])) ? 0 : op.fn;  // 1 needs to be replaced with error code
            break;
            case FN_RandomizeMatrix: //Sub Procedure
                RandomizeMatrix(op.n[0], op.n[1], op.n[2]);
            break;
            case FN_SetMatrixValue: //Sub Procedure
                SetMatrixValue(op.n[0], op.n[1], op.n[2], op.n[3]);
            break;
            case FN_ScalarMatrix: //Sub Procedure
                ScalarMatrix(op.n[0], op.n[1], op.n[2]);
            break;
            case FN_ScalarMatrixColumns: //Number Function
                rc_subprocess_error[0] = (ScalarMatrixColumns(op.n[0], op.n[1], op.n[2], op.n[3], op.n[4])) ? 0 : op.fn;  // 1 needs to be replaced with error code
            break;
            case FN_ScalarMatrixRows: //Number Function
                rc_subprocess_error[0] = (ScalarMatrixRows(op.n[0], op.n[1], op.n[2], op.n[3], op.n[4])) ? 0 : op.fn;  // 1 needs to be replaced with error code
            break;
            case FN_SquareMatrix: //Number Function
                rc_subprocess_error[0] = (SquareMatrix(op.n[0], op.n[1])) ? 0 : op.fn;  // 1 needs to be replaced with error code
            break;
            case FN_SubMatrix: //Sub Procedure
                SubMatrix(op.n[0],  op.n[1], op.n[2]);
            break;
            case FN_SubtractMatrix: //Number Function
                rc_subprocess_error[0] = (SubtractMatrix(op.n[0], op.n[1], op.n[2])) ? 0 : op.fn;  // 1 needs to be replaced with error code
            break;
            case FN_SwapMatrix: //Sub Procedure
                SwapMatrix(op.n[0], op.n[1]);  // 1 needs to be replaced with error code
            break;
            case FN_SwapMatrixColumn: //Number Function
            rc_subprocess_error[0] = (SwapMatrixColumn(op.n[0], op.n[1], op.n[2])) ? 0 : op.fn;  // 1 needs to be replaced with error code
            break;
            case FN_SwapMatrixRow: //Number Function
                rc_subprocess_error[0] = (SwapMatrixRow(op.n[0], op.n[1], op.n[2])) ? 0 : op.fn;  // 1 needs to be replaced with error code
            break;
            case FN_TransposeMatrix: //Number Function
                rc_subprocess_error[0] = (TransposeMatrix(op.n[0], op.n[1])) ? 0 : op.fn;  // 1 needs to be replaced with error code
            break;
            case FN_UnAugmentMatrix: //Number Function
                rc_subprocess_error[0] = (UnAugmentMatrix(op.n[0], op.n[1], op.n[2])) ? 0 : op.fn;  // 1 needs to be replaced with error code
            break;
            case FN_ZeroMatrix: //Sub Procedure
                ZeroMatrix(op.n[0]);
            break;
            case FN_ProcessSleep: //Sub Procedure
                SDL_Delay(op.n[0]);
            break;

        }

        if(rc_subprocess_error != 0)
        {
            rc_subprocess_error_status[process_num] = rc_subprocess_error_mode[process_num];
        }

        rc_unlockMutex(process_num, RC_ERROR_MODE_MUTEX);
        rc_unlockMutex(process_num, RC_CURRENT_OP_MUTEX);

    }

    //std::cout << "thread end " << process_num << std::endl;

    return 0;

}


bool rc_setMatrixProcess(uint32_t p_num)
{
    if(p_num >= 0 && p_num < MAX_SUBPROCESS)
        rc_active_matrix_process = p_num;
    else
        rc_active_matrix_process = -1;

    if(rc_active_matrix_process >= 0)
        return (rc_subprocess_thread[rc_active_matrix_process] != NULL);

    return true; //main process is set
}

bool rc_processOpen(uint32_t p_num)
{
    if(p_num < 0 || p_num >= MAX_SUBPROCESS)
        return false;

    if(rc_subprocess_thread[p_num])
        return false;

    rc_subprocess_thread[p_num] = SDL_CreateThread(rc_subprocess_fn, "rc_subprocess", &rc_subprocess_param[0]);

    return (rc_subprocess_thread[p_num] != NULL);
}

void rc_setProcessErrorMode(uint32_t p_num, uint32_t error_mode)
{
    if(p_num < 0 || p_num >= MAX_SUBPROCESS)
        return;

    rc_lockMutex(p_num, RC_ERROR_MODE_MUTEX);
    rc_subprocess_error_mode[p_num] = error_mode;
    rc_unlockMutex(p_num, RC_ERROR_MODE_MUTEX);
}

int ProcessError(uint32_t p_num)
{
     if(p_num < 0 || p_num >= MAX_SUBPROCESS)
        return 0;

    rc_lockMutex(p_num, RC_ERROR_MODE_MUTEX);
    uint32_t error_mode = rc_subprocess_error_mode[p_num];
    rc_unlockMutex(p_num, RC_ERROR_MODE_MUTEX);

    return error_mode;
}

void ProcessWait(uint32_t p_num)
{
    if(p_num < 0 || p_num >= MAX_SUBPROCESS)
        return;

    if(!rc_subprocess_thread[p_num])
        return;

    rc_lockMutex(p_num, RC_QUEUE_MUTEX);
    uint32_t q_size = rc_subprocess_queue[p_num].op.size();
    rc_unlockMutex(p_num, RC_QUEUE_MUTEX);

    while(q_size > 0)
    {
        rc_lockMutex(p_num, RC_QUEUE_MUTEX);
        q_size = rc_subprocess_queue[p_num].op.size();
        rc_unlockMutex(p_num, RC_QUEUE_MUTEX);
    }

}

void ProcessWaitAll()
{
    for(uint32_t i = 0; i < MAX_SUBPROCESS; i++)
        ProcessWait(i);
}

void ProcessContinue(uint32_t p_num)
{
    if(p_num < 0 || p_num >= MAX_SUBPROCESS)
        return;

    rc_unlockMutex(p_num, RC_CURRENT_OP_MUTEX);
}

void ProcessContinueAll()
{
    for(uint32_t i = 0; i < MAX_SUBPROCESS; i++)
        ProcessContinue(i);
}

void ProcessStop(uint32_t p_num)
{
    if(p_num < 0 || p_num >= MAX_SUBPROCESS)
        return;

    rc_lockMutex(p_num, RC_CURRENT_OP_MUTEX);
}

void ProcessStopAll()
{
    for(uint32_t i = 0; i < MAX_SUBPROCESS; i++)
        ProcessStop(i);
}

void ProcessClear(uint32_t p_num)
{
    if(p_num < 0 || p_num >= MAX_SUBPROCESS)
        return;

    rc_lockMutex(p_num, RC_QUEUE_MUTEX);
    uint32_t q_size = rc_subprocess_queue[p_num].op.size();

    for(uint32_t i = 0; i < q_size; i++)
        rc_subprocess_queue[p_num].op.pop();

    rc_unlockMutex(p_num, RC_QUEUE_MUTEX);
}

bool ProcessClose(uint32_t p_num)
{
    if(p_num < 0 || p_num >= MAX_SUBPROCESS)
        return false;

    if(!rc_subprocess_thread[p_num])
        return false;

    rc_process_op op;
    op.fn = 0;

    rc_lockMutex(p_num, RC_QUEUE_MUTEX);
    rc_subprocess_queue[p_num].op.push(op);
    rc_unlockMutex(p_num, RC_QUEUE_MUTEX);

    SDL_WaitThread(rc_subprocess_thread[p_num], NULL);

    rc_subprocess_thread[p_num] = NULL;

    return true;
}

uint32_t ProcessErrorMode(uint32_t p_num)
{
    if(p_num < 0 || p_num >= MAX_SUBPROCESS)
        return 0;

    rc_lockMutex(p_num, RC_ERROR_MODE_MUTEX);
    uint32_t error_mode = rc_subprocess_error_mode[p_num];
    rc_unlockMutex(p_num, RC_ERROR_MODE_MUTEX);
    return error_mode;
}

void ProcessSleep(uint32_t p_num, uint32_t msec)
{
    if(p_num < 0 || p_num >= MAX_SUBPROCESS)
        return;

    rc_process_op op;
    op.fn = FN_ProcessSleep;
    op.n[0] = msec;

    rc_lockMutex(p_num, RC_QUEUE_MUTEX);
    rc_subprocess_queue[p_num].op.push(op);
    rc_unlockMutex(p_num, RC_QUEUE_MUTEX);
}

bool ProcessExists(uint32_t p_num)
{
    if(p_num < 0 || p_num >= MAX_SUBPROCESS)
        return false;

    return (rc_subprocess_thread[p_num] != NULL);
}

void ProcessQueueMatrixOp(uint32_t fn, double n0 = 0, double n1 = 0, double n2 = 0, double n3 = 0, double n4 = 0, double n5 = 0,
                          double n6 = 0, double n7 = 0, double n8 = 0, double n9 = 0)
{
    rc_process_op op;
    op.fn = fn;
    op.n[0] = n0;
    op.n[1] = n1;
    op.n[2] = n2;
    op.n[3] = n3;
    op.n[4] = n4;
    op.n[5] = n5;
    op.n[6] = n6;
    op.n[7] = n7;
    op.n[8] = n8;
    op.n[9] = n9;

    rc_lockMutex(rc_active_matrix_process, RC_QUEUE_MUTEX);
    rc_subprocess_queue[rc_active_matrix_process].op.push(op);
    rc_unlockMutex(rc_active_matrix_process, RC_QUEUE_MUTEX);
}

void rc_cleanSubprocessSystem()
{
    for(int i = 0; i < MAX_SUBPROCESS; i++)
    {
        ProcessClose(i);
        SDL_DestroyMutex(rc_subprocess_mutex[i].current_op_mutex);
        SDL_DestroyMutex(rc_subprocess_mutex[i].error_mode_mutex);
        SDL_DestroyMutex(rc_subprocess_mutex[i].queue_mutex);
    }
}

int NumCPUs()
{
    return SDL_GetCPUCount();
}

#endif // RC_PROCESS_H_INCLUDED
