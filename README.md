# Banking-System
Bank Transaction Processing System

This project implements a Bank Transaction Processing System using a doubly linked list (DLL) and a singly linked list (SLL). The system maintains bank accounts and processes a series of transactions, providing various functionalities such as processing, undoing, inserting, and deleting transactions. The initial balance for each account is set to 1000 units.

Features:

Account Management: Stores accounts in a singly linked list, each account having a unique account number and a current balance.

Transaction Management: Stores transactions in a doubly linked list, allowing deposits and withdrawals.

Cursor-Based Processing: Maintains a cursor to process transactions, which can be moved forward or backward to process or undo transactions.

Commands: Supports various commands to manipulate and query the transactions and accounts.


Commands:

F X: Process the next X transactions after the cursor.

R Y: Undo Y transactions starting from the cursor.

I T K: Insert a new transaction T immediately after the Kth transaction.

D A M: Delete up to M transactions of account A after/before the cursor's transaction.

C: Process all transactions after the cursor.

S Y: Print all the processed transactions of account number Y.

G X: Print the count of accounts with a balance greater than or equal to X.

M: Print the account number with the highest balance.

V X: Print the balance of account number X.

END: Terminate the program.


Input Format:

The first line specifies the number of accounts (C).

The second line contains C space-separated unsigned integers representing account numbers.

The third line specifies the number of transactions (N).

The next N lines specify transactions in the format: AccountNo D y or AccountNo W x.

Each following line contains a processing directive as described above.

The last line contains only the word END.


Output:

The output of each command will be printed to the standard output as applicable.

Example

Input:

5

718 270 113 431 536

10

270 D 10

431 W 50

536 D 20

536 W 70

113 D 100

718 W 900

113 W 400

431 D 240

270 W 120

113 D 200

F 3

G 1010

M

V 113

V 536

R 2

G 1010

V 536

F 8

V 270

D 270 -2

V 270

C

G 1010

M

END


Output:

2

536

1000

1020

1

1000

890

1000

1

431


Implementation Details

Accounts List: Implemented as a singly linked list with Node *first, Node *last, and int len.

Transactions List: Implemented as a doubly linked list with header and trailer nodes to facilitate easy insertion and deletion.

Cursor: Initially set to the head node in the DLL and can be moved forward or backward as needed.


Constraints

The number of accounts (C) is ≤ 100.

Account numbers are unsigned integers less than 10,000.

Deposit and withdrawal amounts are non-negative integers ≤ 50,000.
