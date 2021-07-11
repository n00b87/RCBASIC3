PRG_NAME$ = "rcx"
PRG_LOCATION$ = "/home/n00b/Desktop/projects/rcbasic_312/dk_adventure"

DST_LOCATION$ = Dir$+"/wasm"

SetEnv("PROG_NAME", PRG_NAME$, 1)
SetEnv("PROG_LOCATION", PRG_LOCATION$ + "@/", 1)
SetEnv("OUT_HTML", DST_LOCATION$+"/"+PRG_NAME+".html", 1)

If Not DirExists(Dir$+"/wasm") Then
	MakeDir("wasm")
End If

System("chmod u+x em_setup.sh && ./em_setup.sh")

CopyFile("resources/rcb.html", DST_LOCATION$+"/tmp.html")
CopyFile("resources/banner.png", DST_LOCATION$+"/banner.png")
CopyFile("resources/style.css", DST_LOCATION$+"/style.css")

FileOpen(0, DST_LOCATION$+"/tmp.html", TEXT_INPUT)
html$=""
While Not EOF(0)
	html$=html$+ReadLine(0)+"\n"
Wend
FileClose(0)

RemoveFile(DST_LOCATION$+"/tmp.html")
'RemoveFile(DST_LOCATION$+"/"+PRG_NAME+".html")

If Not FileExists(DST_LOCATION$+"/"+PRG_NAME+".html") Then
	FileOpen(0, DST_LOCATION$+"/index.html", TEXT_OUTPUT_PLUS)
	WriteLine(0, Replace(html$, "%SOURCE_JS%", PRG_NAME$+".js"))
	FileClose(0)
End If

Print "finished"
