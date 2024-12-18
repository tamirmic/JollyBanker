This program is designed to provide hands-on experience with both queues and binary search trees while allowing for further program and class design. The project offers flexibility in class structure and design, which means there is room for interpretation and creativity.

The program simulates a banking application that processes various types of transactions. The application is split into three phases. In Phase 1, the program reads a series of transactions from a file into an in-memory queue. These transactions may include opening accounts, withdrawing funds, depositing funds, transferring funds, or printing transaction histories. In Phase 2, the program processes these transactions sequentially, reading from the queue and executing them one by one. Once the queue is emptied, Phase 3 begins, where the program prints out all open accounts and their corresponding balances. The program will work with transactions that manipulate client accounts, each of which contains up to eight funds. These transactions will be processed based on a well-formed input file. The program must also handle various types of semantic errors such as insufficient funds, invalid account numbers, or invalid fund IDs, and it will print error messages when such issues arise.

The program supports five types of transactions, each identified by a specific character at the beginning of the line:
O: Open a client account with eight funds, all initialized to zero.
D: Deposit a specified amount into a specific fund.
W: Withdraw a specified amount from a specific fund.
T: Transfer assets between two funds (either within the same account or between different accounts).
A: Display the transaction history for a specific client account.
F: Display the transaction history for a specific fund within a client’s account.

While the input format is assumed to be correct, the program should gracefully handle errors in the transactions themselves. For example, a withdrawal may attempt to take more money than is available in a fund, or a transaction may involve a non-existent account. The program should print appropriate error messages to cerr for such issues. For example, if a client attempts to withdraw from a fund that doesn't have enough assets, the program should display an error message.
