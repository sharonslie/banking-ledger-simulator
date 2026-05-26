# Banking Ledger Simulator

A C++ console application that simulates a banking ledger with support for single, shared, and dual account types — built as a university assignment for Programming Fundamentals at The Hong Kong Polytechnic University.

---

## What It Does

The program manages a ledger of bank accounts stored as a global array of struct pointers, linked together to represent account relationships. It supports:

- **Single accounts** — owned by one person
- **Shared accounts** — another account holder has access and can withdraw
- **Dual accounts** — two accounts belonging to the same person, linked to each other

---

## Features

### `populate()`
Initializes the ledger with 5 hardcoded accounts across 4 account holders (Tayyab, Alex, Jeff, Xavier), each starting with a $100.00 balance. Pointer links between accounts define the shared/dual relationships.

### `withdraw(title, account_number, amount)`
Handles withdrawal logic with the following rules:
- The requester must be the direct owner **or** a linked shared-account holder
- A **2% fee** applies to shared-access withdrawals
- A **3% fee** applies to non-premium (standard) accounts
- Withdrawal is rejected if the balance would go negative

### `display_ledger()`
Prints a formatted summary of all accounts, automatically:
- Groups dual accounts into a single display row
- Labels shared accounts and their co-holders
- Skips duplicate entries for dual-account pairs

---

## Concepts Used

| Concept | Where Used |
|---|---|
| Structs | `Account` struct with fields for title, number, premium status, balance, and next pointer |
| Pointer arrays | `ledger` is a global array of `Account*` pointers |
| Linked structures | `Account->Next` links accounts to model shared/dual relationships |
| Dynamic memory | Accounts allocated with `new` |
| String handling | `strcpy`, `strcmp` from `<cstring>` |
| Formatted output | `<iomanip>` for fixed-precision balance display |

---

## Sample Output

```
Title: Tayyab
Account # 1
Type: Premium
Balance: $20.00

Title: Alex
Account # 2
Type: Standard
Balance: $51.50

Title: Jeff        Tayyab (Shared)
Account # 3
Type: Standard
Balance: $35.71

Title: Xavier (Dual)
Account # 4        5
Type: Standard     Premium
Balance: $12.43    $100.00
```

---

## How to Run

1. Clone the repository
2. Open in any C++ IDE (e.g. Visual Studio, CLion, VS Code with g++)
3. Compile and run `main.cpp`

```bash
g++ main.cpp -o ledger
./ledger
```

> Requires C++11 or later. The `_CRT_SECURE_NO_WARNINGS` define suppresses MSVC warnings for `strcpy` — safe to remove on non-Windows compilers.

---

## Project Context

- **Course:** Programming Fundamentals
- **University:** The Hong Kong Polytechnic University
- **Semester:** Spring 2026
- **Language:** C++
