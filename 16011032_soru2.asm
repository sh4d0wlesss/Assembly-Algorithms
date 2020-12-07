myss	SEGMENT PARA STACK 'yıgın'
	    DW 100 DUP(?)
myss 	ENDS

myds 	SEGMENT PARA 'veri'
CR		EQU	13
LF		EQU	10
HATA	DB	CR,LF,' -128 ile 127 arasinda sayi girmediniz yeniden giriniz:',0
dizi	DB  100 DUP(?)                                    
n		DB 0 ;ELEMAN SAYISI
LOWPTR	DB 0 ;SOLDAKİ POİNTERİM
HIGHPTR	DB ? ;SAĞDAKİ POİNTERİM
Mesaj1		DB	CR,LF,'lutfen eleman sayisini giriniz: ',0
Mesaj2	DB	CR,LF,'lutfen elemanlari giriniz: ',0
myds ENDS

mycs	SEGMENT PARA 'kod'
		ASSUME CS:mycs, DS:myds, SS:myss
BASLA PROC FAR
		PUSH DS
		XOR AX,AX
		PUSH AX
		MOV AX,myds
		MOV DS,AX
		
		LEA AX,Mesaj1
		CALL PUT_STR
		CALL GETN
		MOV n,AL
		DEC AL
		MOV HIGHPTR,AL
		
		XOR DI,DI
		XOR CX,CX
		MOV CL,n


		JMP zıpla 
tekrar:	LEA AX,HATA 
		CALL PUT_STR
		
zıpla:	LEA AX,Mesaj2
		CALL PUT_STR
;--------elemanları alıyoruz
EL_AL:	CALL GETN
		CMP AX,-128
		JL tekrar
		CMP AX, 127
		JG tekrar
		MOV dizi[DI],AL
		INC DI
		LOOP EL_AL 
;----------------------------
		CALL QUICKSORT
		
		XOR CX,CX
		MOV CL,n
		XOR AX,AX
		XOR DI,DI
		
EL_YAZ: MOV AL,dizi[DI]
		CALL PUTN
		MOV AL,32
		CALL PUTC
		INC DI
		LOOP EL_YAZ
		
		
		RETF
BASLA	ENDP

;-------------------------------QUICKSORT FONKSİYONU------------------
QUICKSORT	PROC NEAR
			XOR BX,BX
			MOV BL,LOWPTR
			MOV DI,BX
			
			MOV BL,HIGHPTR
			MOV SI,BX
			
			MOV AX,DI   ;AX E DI VE SI YI ATARAK N-1 YAPIP 2 YE BÖLEREK PİVOT OLUSTURACAGIZ DİZİNİN ORTASINDAN
			ADD AX,SI
			SHR AX,1
			
			MOV BX,AX
			MOV DL,dizi[BX] ;BURADA DİZİNİN ORTASINDAKİ DEĞEĞRİ PİVOT OLARAK SEÇİYORUZ
			
			
L1:			CMP	DI,SI
			JA SOLUSIRALA
			
L2:			CMP dizi[DI],DL
			JGE	ATLA1
			INC	DI
			JMP L2
			
ATLA1:		CMP dizi[SI],DL
			JLE ATLA2
			DEC SI
			JMP ATLA1
			
ATLA2:		CMP DI,SI
			JA	L1
			MOV DH,dizi[DI]
			XCHG DH,dizi[SI]
			MOV dizi[DI],DH
			INC DI
			CMP SI,0
			JE L1
			DEC SI
			JMP L1
			
			
SOLUSIRALA:	XOR AX,AX
			MOV AL,LOWPTR
			CMP AX,SI
			JAE SAGISIRALA
			MOV AX,SI
			MOV HIGHPTR,AL
			CALL QUICKSORT 
			
SAGISIRALA:	MOV AL,n
			DEC AL
			MOV HIGHPTR,AL    
			XOR AX,AX
			MOV AL,HIGHPTR
			CMP DI,AX
			JAE BİTİS
			MOV AX,DI
			MOV LOWPTR,AL
			CALL QUICKSORT
			
BİTİS:		RET
QUICKSORT	ENDP	
			
;----------------------------------------------------------------------------------------------------		
;-------------------------------------------klavyeden basılan sayıyı okur ----------------------------
GETN	PROC NEAR
		PUSH BX
		PUSH CX
		PUSH DX
GETN_START:
		MOV DX,1
		XOR BX,BX
		XOR CX,CX
NEW:
		CALL GETC
		CMP AL,CR
		JE FIN_READ
		CMP AL, '-'
		JNE CTRL_NUM
NEGATIVE:
		MOV DX,-1
		JMP NEW
CTRL_NUM:
		CMP AL,'0'
		JB error
		CMP AL,'9'
		JA error
		SUB AL, '0'
		MOV BL,AL
		MOV AX,10
		PUSH DX
		MUL CX
		POP DX
		MOV CX,AX
		ADD CX,BX
		JMP NEW
error:
		MOV AX, OFFSET HATA
		CALL PUT_STR
		JMP GETN_START
FIN_READ:
		MOV AX,CX
		CMP DX,1
		JE FIN_GETN
		NEG AX
FIN_GETN:
		POP BX
		POP CX
		POP DX
		RET
GETN    ENDP
;----------------------------------------------ax de bulunan sayıyı onluk tabanda hane hane yazdırır-----------------------------
PUTN	PROC NEAR
		PUSH CX
		PUSH DX
		XOR DX,DX
		PUSH DX
		MOV CL,10
		CMP AL,0
		JGE CALC_DIGITS
		NEG AL
		PUSH AX
		MOV AL, '-'
		CALL PUTC
		POP AX
CALC_DIGITS:
		DIV CL
		ADD AH, '0'
		MOV DL,AH
		PUSH DX
		XOR AH,AH
		CMP AL,0
		JNE CALC_DIGITS
DISP_LOOP:
		POP AX
		CMP AL,0
		JE END_DISP_LOOP
		CALL PUTC
		JMP DISP_LOOP
END_DISP_LOOP:
		POP DX
		POP CX
		RET
PUTN	ENDP
;--------------------------------------------------------al yazmacındaki değeri ekranda gösterir------------------------------
PUTC	PROC NEAR
		PUSH AX
		PUSH DX
		MOV DL,AL
		MOV AH,2
		INT 21H
		POP DX
		POP AX
		RET
PUTC	ENDP 

GETC 	PROC NEAR
		MOV AH,1h
		INT 21H
		RET
GETC 	ENDP
;------------------------------------------------------------ax de adresi verilen sonunda 0 olan dizgeyi karakter karakter yazdırır------------------
PUT_STR	PROC NEAR
		PUSH BX
		MOV BX,AX
		MOV AL,BYTE PTR [BX]
PUT_LOOP:
		CMP AL,0
		JE PUT_FIN
		CALL PUTC
		INC BX
		MOV AL,BYTE PTR [BX]
		JMP PUT_LOOP
PUT_FIN:
		POP BX
		RET
PUT_STR	ENDP

mycs ENDS
    END BASLA