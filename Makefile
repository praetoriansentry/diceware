DW_BIN:=diceware
$(DW_BIN):
	gcc -o $(DW_BIN) main.c
test:
	@echo "Running Diceware"
	./$(DW_BIN)
clean:
	$(RM) $(DW_BIN)
