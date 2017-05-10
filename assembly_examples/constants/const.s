.data
.byte 74, 0x4A, 'J' 
.align 4
.ascii "Ring the bell\7" 
.text
.ascii "Lives in the  text section *"
.data 
.ascii "Lives in the data section,"
.ascii "Null terminated,\0"
.ascii "Another string"	
.text 
.ascii "Lives in the text section,"
.ascii "following the asterisk (*)."
.align 4
.comm foo , 64, 4
	