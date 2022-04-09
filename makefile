
all : exe

exe : main.c prod.h
	gcc main.c prod.h -o exe

clean :
	rm -rf exe alerte.txt
	cp stock_de_base.txt stock.txt
	rm -r factures
	mkdir factures
