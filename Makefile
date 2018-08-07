DW_BIN:=diceware
$(DW_BIN):
	gcc -std=c99 -o $(DW_BIN) main.c
test:
	@echo "Running Diceware"
	./$(DW_BIN)
clean:
	$(RM) $(DW_BIN)
