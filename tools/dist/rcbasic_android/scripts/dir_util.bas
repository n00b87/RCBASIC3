Include "strings.bas"
Include Once

Function SourceDirectory$()
	current_file$ = Command$(0)
	cwd$ = Dir$
	end_of_dir = Max( FindLastOf("\\", current_file$), FindLastOf("/", current_file$) )
	end_of_dir = Max( end_of_dir, 0 )	
	current_file_dir$ = ""
	If Trim$(Left$(current_file$, end_of_dir)) <> "" Then
		ChangeDir(Left$(current_file$, end_of_dir))
	End If
	current_file_dir$ = Dir$
	ChangeDir(cwd$)

	return current_file_dir$
End Function
