all: clean leader member

clean:
	rm -f leader
	rm -f member

leader:
	gcc -o leader leader.c -L . -lm2tp-leader

member:
	gcc -o member member.c -L . -lm2tp-member

.PHONY: all clean leader member