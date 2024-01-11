#ifndef RC_PROCESS_H_INCLUDED
#define RC_PROCESS_H_INCLUDED

#include <iostream>
#ifdef RC_ANDROID
	#include "SDL.h"
#else
	#include <SDL2/SDL.h>
#endif
#include <queue>
#include "rc_matrix.h"
#include "rc_defines.h"

#define MAX_SUBPROCESS 3

#define RC_THREAD_ONERROR_CONTINUE 0
#define RC_THREAD_ONERROR_STOP 1

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
    int fn;
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

void rc_lockMutex(int process_num, uint32_t m)
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

void rc_unlockMutex(int process_num, uint32_t m)
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
            rc_unlockMutex(process_num, RC_QUEUE_MUTEX);
        }
        else
            rc_unlockMutex(process_num, RC_QUEUE_MUTEX);

        rc_lockMutex(process_num, RC_CURRENT_OP_MUTEX);
        rc_lockMutex(process_num, RC_ERROR_MODE_MUTEX);

        switch(op.fn)
        {
            case 0:
                p_loop = false; //std::cout << "THREAD_END_OP " << std::endl;
                break;

            case FN_DimMatrix: //Sub Procedure
                DimMatrix(op.n[0], op.n[1], op.n[2], op.n[3]);
            break;
            case FN_AddMatrix: //Number Function
                rc_subprocess_error[process_num] = (AddMatrix(op.n[0], op.n[1], op.n[2])) ? 0 : op.fn;
            break;
            case FN_AugmentMatrix: //Number Function
                rc_subprocess_error[process_num] = (AugmentMatrix(op.n[0], op.n[1], op.n[2])) ? 0 : op.fn;
            break;
            case FN_CopyMatrix: //Sub Procedure
                CopyMatrix(op.n[0], op.n[1]);
            break;
            case FN_InsertMatrixColumns: //Number Function
                rc_subprocess_error[process_num] = (InsertMatrixColumn(op.n[0], op.n[1], op.n[2])) ? 0 : op.fn;
            break;
            case FN_InsertMatrixRows: //Number Function
                rc_subprocess_error[process_num] = (InsertMatrixRow(op.n[0], op.n[1], op.n[2])) ? 0 : op.fn;
            break;
            case FN_MultiplyMatrix: //Number Function
                rc_subprocess_error[process_num] = (MultiplyMatrix(op.n[0], op.n[1], op.n[2])) ? 0 : op.fn;
            break;
            case FN_CubeMatrix: //Number Function
                rc_subprocess_error[process_num] = (CubeMatrix(op.n[0], op.n[1], process_num)) ? 0 : op.fn;
            break;
            case FN_DeleteMatrixColumns: //Number Function
                rc_subprocess_error[process_num] = (DeleteMatrixColumns(op.n[0], op.n[1], op.n[2], process_num)) ? 0 : op.fn;
            break;
            case FN_DeleteMatrixRows: //Number Function
                rc_subprocess_error[process_num] = (DeleteMatrixRows(op.n[0], op.n[1], op.n[2])) ? 0 : op.fn;
            break;
            case FN_ClearMatrix: //Sub Procedure
                ClearMatrix(op.n[0]);
            break;
            case FN_ClearMatrixColumns: //Number Function
                rc_subprocess_error[process_num] = (ClearMatrixColumns(op.n[0], op.n[1], op.n[2])) ? 0 : op.fn;
            break;
            case FN_ClearMatrixRows: //Number Function
                rc_subprocess_error[process_num] = (ClearMatrixRows(op.n[0], op.n[1], op.n[2])) ? 0 : op.fn;
            break;
            case FN_FillMatrix: //Sub Procedure
                FillMatrix(op.n[0], op.n[1]);
            break;
            case FN_FillMatrixColumns: //Number Function
                rc_subprocess_error[process_num] = (FillMatrixColumns(op.n[0], op.n[1], op.n[2], op.n[3])) ? 0 : op.fn;
            break;
            case FN_FillMatrixRows: //Number Function
                rc_subprocess_error[process_num] = (FillMatrixRows(op.n[0], op.n[1], op.n[2], op.n[3])) ? 0 : op.fn;
            break;
            case FN_CopyMatrixColumns: //Number Function
                rc_subprocess_error[process_num] = (GetMatrixColumns(op.n[0], op.n[1], op.n[2], op.n[3])) ? 0 : op.fn;  // 1 needs to be replaced with error code
            break;
            case FN_CopyMatrixRows: //Number Function
                rc_subprocess_error[process_num] = (GetMatrixRows(op.n[0], op.n[1], op.n[2], op.n[3])) ? 0 : op.fn;  // 1 needs to be replaced with error code
            break;
            case FN_IdentityMatrix: //Sub Procedure
                IdentityMatrix(op.n[0], op.n[1]);
            break;
            case FN_SolveMatrix: //Number Function
                rc_subprocess_error[process_num] = (SolveMatrix(op.n[0], op.n[1], op.n[2])) ? 0 : op.fn;  // 1 needs to be replaced with error code
            break;
            case FN_IsEqualMatrix: //Number Function
                rc_subprocess_error[process_num] = (IsEqualMatrix(op.n[0], op.n[1], op.n[2])) ? 0 : op.fn;  // 1 needs to be replaced with error code
            break;
            case FN_AdjointMatrix: //Number Function
                rc_subprocess_error[process_num] = (AdjointMatrix(op.n[0], op.n[1])) ? 0 : op.fn;  // 1 needs to be replaced with error code
            break;
            case FN_InvertMatrix: //Number Function
                rc_subprocess_error[process_num] = (InvertMatrix(op.n[0], op.n[1])) ? 0 : op.fn;  // 1 needs to be replaced with error code
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
                rc_subprocess_error[process_num] = (ScalarMatrixColumns(op.n[0], op.n[1], op.n[2], op.n[3], op.n[4])) ? 0 : op.fn;  // 1 needs to be replaced with error code
            break;
            case FN_ScalarMatrixRows: //Number Function
                rc_subprocess_error[process_num] = (ScalarMatrixRows(op.n[0], op.n[1], op.n[2], op.n[3], op.n[4])) ? 0 : op.fn;  // 1 needs to be replaced with error code
            break;
            case FN_SquareMatrix: //Number Function
                rc_subprocess_error[process_num] = (SquareMatrix(op.n[0], op.n[1])) ? 0 : op.fn;  // 1 needs to be replaced with error code
            break;
            case FN_SubMatrix: //Sub Procedure
                SubMatrix(op.n[0],  op.n[1], op.n[2]);
            break;
            case FN_SubtractMatrix: //Number Function
                rc_subprocess_error[process_num] = (SubtractMatrix(op.n[0], op.n[1], op.n[2])) ? 0 : op.fn;  // 1 needs to be replaced with error code
            break;
            case FN_SwapMatrix: //Sub Procedure
                SwapMatrix(op.n[0], op.n[1], process_num);  // 1 needs to be replaced with error code
            break;
            case FN_SwapMatrixColumn: //Number Function
            rc_subprocess_error[process_num] = (SwapMatrixColumn(op.n[0], op.n[1], op.n[2])) ? 0 : op.fn;  // 1 needs to be replaced with error code
            break;
            case FN_SwapMatrixRow: //Number Function
                rc_subprocess_error[process_num] = (SwapMatrixRow(op.n[0], op.n[1], op.n[2])) ? 0 : op.fn;  // 1 needs to be replaced with error code
            break;
            case FN_TransposeMatrix: //Number Function
                rc_subprocess_error[process_num] = (TransposeMatrix(op.n[0], op.n[1])) ? 0 : op.fn;  // 1 needs to be replaced with error code
            break;
            case FN_UnAugmentMatrix: //Number Function
                rc_subprocess_error[process_num] = (UnAugmentMatrix(op.n[0], op.n[1], op.n[2])) ? 0 : op.fn;  // 1 needs to be replaced with error code
            break;
            case FN_ZeroMatrix: //Sub Procedure
                ZeroMatrix(op.n[0]);
            break;
            case FN_ProcessSleep: //Sub Procedure
                SDL_Delay(op.n[0]);
            break;

        }

        if(op.fn >= 0)
        {
            rc_lockMutex(process_num, RC_QUEUE_MUTEX);
            if(rc_subprocess_queue[process_num].op.size()>0)
                rc_subprocess_queue[process_num].op.pop();
            rc_unlockMutex(process_num, RC_QUEUE_MUTEX);
        }

        if(rc_subprocess_error[process_num] != 0)
        {
            switch(rc_subprocess_error_mode[process_num])
            {
                case RC_THREAD_ONERROR_CONTINUE:
                    rc_unlockMutex(process_num, RC_ERROR_MODE_MUTEX);
                    break;
                case RC_THREAD_ONERROR_STOP:
                    rc_unlockMutex(process_num, RC_ERROR_MODE_MUTEX);
                    bool error_status = true;
                    while(error_status)
                    {
                        rc_lockMutex(process_num, RC_ERROR_MODE_MUTEX);
                        error_status = (rc_subprocess_error[process_num] != 0);
                        rc_unlockMutex(process_num, RC_ERROR_MODE_MUTEX);
                        //std::cout << "THREAD_ERROR " << error_status << std::endl;
                        SDL_Delay(5);
                    }
                    break;
            }
        }
        else
            rc_unlockMutex(process_num, RC_ERROR_MODE_MUTEX);

        rc_unlockMutex(process_num, RC_CURRENT_OP_MUTEX);

    }

    //std::cout << "thread end " << process_num << std::endl;

    return 0;

}


bool rc_setMatrixProcess(int p_num)
{
    if(p_num >= 0 && p_num < MAX_SUBPROCESS)
        rc_active_matrix_process = p_num;
    else
        rc_active_matrix_process = -1;

    if(rc_active_matrix_process >= 0)
        return (rc_subprocess_thread[rc_active_matrix_process] != NULL);

    return true; //main process is set
}

bool rc_processOpen(int p_num)
{
    if(p_num < 0 || p_num >= MAX_SUBPROCESS)
        return false;

    if(rc_subprocess_thread[p_num])
        return false;

    for(int i = 0; i < rc_subprocess_queue[p_num].op.size(); i++)
        rc_subprocess_queue[p_num].op.pop();

    rc_subprocess_thread[p_num] = SDL_CreateThread(rc_subprocess_fn, "rc_subprocess", &rc_subprocess_param[0]);

    return (rc_subprocess_thread[p_num] != NULL);
}

void rc_setProcessErrorMode(int p_num, uint32_t error_mode)
{
    if(p_num < 0 || p_num >= MAX_SUBPROCESS)
        return;

    if(error_mode < 0 || error_mode > 1)
        error_mode = 0;

    rc_lockMutex(p_num, RC_ERROR_MODE_MUTEX);
    rc_subprocess_error_mode[p_num] = error_mode;
    rc_unlockMutex(p_num, RC_ERROR_MODE_MUTEX);
}

int ProcessError(int p_num)
{
     if(p_num < 0 || p_num >= MAX_SUBPROCESS)
        return 0;

    rc_lockMutex(p_num, RC_ERROR_MODE_MUTEX);
    int error = rc_subprocess_error[p_num];
    rc_unlockMutex(p_num, RC_ERROR_MODE_MUTEX);

    return error;
}

void ProcessWait(int p_num)
{
    if(p_num < 0 || p_num >= MAX_SUBPROCESS)
        return;

    if(!rc_subprocess_thread[p_num])
        return;

    //std::cout << "q_LOCK " << std::endl;
    rc_lockMutex(p_num, RC_QUEUE_MUTEX);
    uint32_t q_size = rc_subprocess_queue[p_num].op.size();
    rc_unlockMutex(p_num, RC_QUEUE_MUTEX);

    //std::cout << "q_size = " << q_size << std::endl;

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

void ProcessContinue(int p_num)
{
    if(p_num < 0 || p_num >= MAX_SUBPROCESS)
        return;

    rc_lockMutex(p_num, RC_ERROR_MODE_MUTEX);
    rc_subprocess_error[p_num] = 0;
    rc_unlockMutex(p_num, RC_ERROR_MODE_MUTEX);

    rc_unlockMutex(p_num, RC_CURRENT_OP_MUTEX);
}

void ProcessContinueAll()
{
    for(uint32_t i = 0; i < MAX_SUBPROCESS; i++)
        ProcessContinue(i);
}

void ProcessStop(int p_num)
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

void ProcessClear(int p_num)
{
    if(p_num < 0 || p_num >= MAX_SUBPROCESS)
        return;

    rc_lockMutex(p_num, RC_QUEUE_MUTEX);
    uint32_t q_size = rc_subprocess_queue[p_num].op.size();

    for(uint32_t i = 0; i < q_size; i++)
        rc_subprocess_queue[p_num].op.pop();

    rc_unlockMutex(p_num, RC_QUEUE_MUTEX);

    rc_lockMutex(p_num, RC_ERROR_MODE_MUTEX);
    rc_subprocess_error[p_num] = 0;
    rc_unlockMutex(p_num, RC_ERROR_MODE_MUTEX);
}

bool ProcessClose(int p_num)
{
    if(p_num < 0 || p_num >= MAX_SUBPROCESS)
        return false;

    if(!rc_subprocess_thread[p_num])
        return false;

    rc_process_op op;
    op.fn = 0;

    ProcessClear(p_num);

    rc_lockMutex(p_num, RC_QUEUE_MUTEX);
    rc_subprocess_queue[p_num].op.push(op);
    rc_unlockMutex(p_num, RC_QUEUE_MUTEX);

    SDL_WaitThread(rc_subprocess_thread[p_num], NULL);

    rc_subprocess_thread[p_num] = NULL;

    if(rc_active_matrix_process == p_num)
        rc_active_matrix_process = -1;

    return true;
}

uint32_t ProcessErrorMode(int p_num)
{
    if(p_num < 0 || p_num >= MAX_SUBPROCESS)
        return 0;

    rc_lockMutex(p_num, RC_ERROR_MODE_MUTEX);
    uint32_t error_mode = rc_subprocess_error_mode[p_num];
    rc_unlockMutex(p_num, RC_ERROR_MODE_MUTEX);
    return error_mode;
}

void ProcessSleep(int p_num, uint32_t msec)
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

bool ProcessExists(int p_num)
{
    if(p_num < 0 || p_num >= MAX_SUBPROCESS)
        return false;

    return (rc_subprocess_thread[p_num] != NULL);
}

uint32_t ProcessQueueSize(int p_num)
{
    rc_lockMutex(p_num, RC_QUEUE_MUTEX);
    int q_size = rc_subprocess_queue[p_num].op.size();
    rc_unlockMutex(p_num, RC_QUEUE_MUTEX);

    return q_size;
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
