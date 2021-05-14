data segment
	;提示信息
	msgInputStr db "Please input a string: $"
	msgInputX db "Please input x from -8 to 8: $"
	msgInputError db "Input Error! Program Exit!$"
	msgAftNone db "String not change, your string is: $"
	msgAftDecode db "After decode, new string is: $"
	msgAftEncode db "After encode, new string is: $"
	msgNewLine db 0AH, 0DH, '$'
	msgTest1 db "test1$"
	msgTest2 db "test2$"
	msgTest3 db "test3$"
	numX db '0' ;X以int形式存储
	strInputX db 3 dup(?) ;输入的X
	strInput db 21 dup(?) ;输入的字符串
	strOutput db 21 dup(?) ;输出的字符串
data ends

code segment
	assume cs:code, ds:data
	;main函数，程序主函数
	main PROC
	start:
		mov ax,data
		mov ds,ax
		call subInput
		;CL标志位，如果为1则代表输入出现错误
		cmp CX, 1
		je proEnd
		call subDoCaesar
	proEnd: ;程序结束
		mov AH, 4CH ;返回DOS系统
        int 21H
	main ENDP
	
	;subInput过程，用于输入数据
	subInput PROC
		;输出字符串提示
		lea BX, msgInputStr
		call funcPrint
		;输入字符串
		lea BX, strInput
		mov CL, 21
		call funcInput
		;输出X提示
		lea BX, msgInputX
		call funcPrint
		;输入X
		lea BX, strInputX
		mov CL, 3
		call funcInput
		;判断X是否合法，长度必须是1或者2
		lea SI, strInputX+1
		mov AL, [SI]
		cmp AL, 1
		jb inpError
		cmp AL, 2
		ja inpError
		mov CX, 0 ;比较过程结束，cx置0为未出错
		jmp inpEnd
	inpError: ;输入过程出错
		lea BX, msgInputError
		call funcPrint
		mov CX, 1 ;CX置1为出错
	inpEnd: ;输入结束
        ret
	subInput ENDP
	
	;subDoCaesar过程，凯撒加密主过程，判断X后调用enCode和deCode
	subDoCaesar PROC
		;判断X是正还是负
		lea SI, strInputX+2
		mov AL, [SI]
		cmp AL, '0' ;0
		je inpIs0
		cmp AL, '-' ;正数
		jne callEnCode
		cmp AL, '-' ;负数
		je callDeCode
		jmp doEnd
	callDeCode: ;负数
		call subDeCode
		jmp doEnd
	callEnCode: ;正数
		mov AL, [SI+1]
		cmp AL, "$"
		jne enCodeErr
		call subEnCode
		jmp doEnd
	enCodeErr:
		lea BX, msgInputError
		call funcPrint
		mov CX, 1
		jmp doEnd
	inpIs0: ;0
		lea BX, msgAftNone
		call funcPrint
		lea BX, strInput+2
		call funcPrint
		lea BX, msgNewLine
		call funcPrint
	doEnd: ;结束地址
		ret
	subDoCaesar ENDP
		
	;subEnCode过程，加密
	subEnCode PROC
		call funcWord2Byte
		cmp CX, 1 ;出错则结束
		je enEnd
		;加密过程
		lea DX, strInput ;循环次数
		mov SI, DX
		mov CX, [SI+1H]
		mov CH, 0H
		mov AX, 2H
		mov SI, AX ;SI为源字符串指针
		mov AX, 2H
		mov DI, AX ;DI为目标字符串指针
		enCodeLoop:
			;加密字符
			mov AL, byte ptr strInput[SI]
			;小于A，大于z不用处理
			cmp AL, 'A'
			jb enCodeFinish
			cmp AL, 'z'
			ja enCodeFinish
			cmp AL, 'a' ;比a大，说明是小写字母
			jae enCodeSmall
			cmp AL, 'Z' ;比Z小，说明是大写字母
			jbe enCodeBig
			jmp enCodeFinish ;都没命中，说明在Z和a之间
		enCodeSmall: ;处理小写字母
			add AL, numX
			cmp AL, 'z'
			ja enCodeSmallOverflow
			jmp enCodeFinish
		enCodeSmallOverflow: ;小写字母比z还大
			sub AL, 26
			jmp enCodeFinish
		enCodeBig: ;处理大写字母
			add AL, numX
			cmp AL, 'Z'
			ja enCodeBigOverflow
			jmp enCodeFinish
		enCodeBigOverflow: ;大写字母比Z还大
			sub AL, 26
			jmp enCodeFinish
		enCodeFinish: ;当前字符加密完成
			mov byte ptr strOutput[DI], AL
			;当前字符加密完成，进行下一个字符
			inc SI
			inc DI
		loop enCodeLoop
		;最后添加结束符号
		mov byte ptr strOutput[DI], '$'
		;完成后输出
		lea BX, msgAftEncode
		call funcPrint
		lea BX, strOutput+2
		call funcPrint
		lea BX, msgNewLine
		call funcPrint
	enEnd: ;结束地址
		ret
	subEnCode ENDP
	
	;subDeCode过程，解密
	subDeCode PROC
		inc SI ;负数需要自增一位
		call funcWord2Byte
		cmp CX, 1 ;出错则结束
		je deEnd
		;解密过程
		lea DX, strInput ;循环次数
		mov SI, DX
		mov CX, [SI+1H]
		mov CH, 0H
		mov AX, 2H
		mov SI, AX ;SI为源字符串指针
		mov AX, 2H
		mov DI, AX ;DI为目标字符串指针
		deCodeLoop:
			;解密字符
			mov AL, byte ptr strInput[SI]
			;小于A，大于z不用处理
			cmp AL, 'A'
			jb deCodeFinish
			cmp AL, 'z'
			ja deCodeFinish
			cmp AL, 'a' ;比a大，说明是小写字母
			jae deCodeSmall
			cmp AL, 'Z' ;比Z小，说明是大写字母
			jbe deCodeBig
			jmp deCodeFinish ;都没命中，说明在Z和a之间
		deCodeSmall: ;处理小写字母
			sub AL, numX
			cmp AL, 'a'
			jb deCodeSmallOverflow
			jmp deCodeFinish
		deCodeSmallOverflow: ;小写字母比a还小
			add AL, 26
			jmp deCodeFinish
		deCodeBig: ;处理大写字母
			sub AL, numX
			cmp AL, 'A'
			jb deCodeBigOverflow
			jmp deCodeFinish
		deCodeBigOverflow: ;大写字母比A还小
			add AL, 26
			jmp deCodeFinish
		deCodeFinish: ;当前字符加密完成
			mov byte ptr strOutput[DI], AL
			;当前字符加密完成，进行下一个字符
			inc SI
			inc DI
		loop deCodeLoop
		;最后添加结束符号
		mov byte ptr strOutput[DI], '$'
		;完成后输出
		lea BX, msgAftDecode
		call funcPrint
		lea BX, strOutput+2
		call funcPrint
		lea BX, msgNewLine
		call funcPrint
	deEnd: ;结束地址
		ret
	subDeCode ENDP
	
	;功能类型函数
	;funcWord2Byte函数，相当于char2int，利用SI为地址缓存，结果返回在内存numX中，CX置1为出错
	funcWord2Byte PROC
		mov AL, [SI] ;读取输入的数
		sub AL, 48 ;ASCII码处理
		mov numX, AL
		cmp AL, 0
		jbe w2bError
		cmp AL, 8
		ja w2bError
		mov CX, 0 ;比较过程结束，cx置0为未出错
		jmp w2bEnd
	w2bError:
		lea BX, msgInputError
		call funcPrint
		mov CX, 1 ;CX置1为出错
	w2bEnd:
		ret
	funcWord2Byte ENDP
	;funcPrint函数，输出标准函数，利用BX为地址缓存
	funcPrint PROC
		;调用DOS输出功能
		mov DX, BX
        mov AH, 09H
        int 21H
		ret
	funcPrint ENDP
	;funcInput函数，输入标准函数，利用BX为地址缓存，CL为最大输入量
	funcInput PROC
		;调用DOS输入功能
	    mov DX, BX
		mov byte ptr [BX], CL
        mov AH, 0AH
        int 21H
		;给字符串末尾添加一个'$'结束符号
		mov SI, DX ;必须用SI寻址
		mov AX, [SI+1H] ;输入字符串的大小在DX+1位置
		add AL, 2
		mov AH, 0
        mov SI, AX
        mov byte ptr [BX+SI], "$"
		;输出一个换行符
        lea DX, msgNewLine
        mov AH, 09H						 
        int 21H
		ret
	funcInput ENDP
code ends
end start