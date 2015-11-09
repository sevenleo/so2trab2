all:	
	@echo "______________________________________________________compilando parte 1"
	@gcc nopen.c -o nopen
	@echo "______________________________________________________compilando parte 2"
	@gcc icount.c -o icount
	@gcc icount.c
	@echo "______________________________________________________________executando"
	@./a.out
	@echo "______________________________________________________________limpando"
	@rm a.out

pwd:
	@echo "______________________________________________________compilando parte 1"
	@gcc nopen.c -o nopen
	@echo "______________________________________________________compilando parte 2"
	@gcc icount.c -o icount
	@gcc icount.c
	@echo "______________________________________________________________executando"
	@./a.out /home/leonardo/ufrj/so2
	@echo "______________________________________________________________limpando"
	@rm a.out


