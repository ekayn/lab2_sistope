build: lab1 hijo

lab1: lab1.o
	@gcc lab1.c -o lab1
	
lab1.o:
	@gcc -c lab1.c
	
hijo: hijo.o
	@gcc hijo.c -o hijo
	
hijo.o:
	@gcc -c hijo.c
	
run1:
	@./lab1 -i datos_juegos.csv -o salida.txt -d 2018 -p 20.90 -b
	
run2:
	@./lab1 -i datos_juegos.csv -o salida.txt -d 2018 -p 20.90

.PHONY:

clean:
	@rm *.o lab1 hijo intermedio.txt salida.txt
