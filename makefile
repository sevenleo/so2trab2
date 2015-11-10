all:	
	@echo "______________________________________________________compilando parte 1"
	@gcc nopen.c -o nopen
	@echo "______________________________________________________compilando parte 2"
	@gcc icount.c -o icount
	@gcc icount.c
	@echo "______________________________________________________________executando"
	@./a.out -d /home/leonardo/ufrj/so2
	@echo "______________________________________________________________limpando"
	@rm a.out

pwd:
	@echo "______________________________________________________compilando parte 1"
	@gcc nopen.c -o nopen
	@echo "______________________________________________________compilando parte 2"
	@gcc icount.c -o icount
	@gcc icount.c
	@echo "______________________________________________________________executando"
	./a.out
	@echo "------------------------------------------------" 
	./a.out -d 
	@echo "------------------------------------------------" 
	./a.out /home/leonardo/ufrj/so2
	@echo "------------------------------------------------" 
	./a.out -d /home/leonardo/ufrj/so2
	@echo "------------------------------------------------" 
	./a.out /home/leonardo/ufrj/so2 -d
	@echo "______________________________________________________________limpando"
	@rm a.out


