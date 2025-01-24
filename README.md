# Supermarket Billing Management System

This project implements a **Supermarket Billing Management System** in C, using doubly linked lists for dynamic item handling and file storage for data persistence. The system provides features for managing a cart, generating bills, and updating item databases.

## Features

1. **Cart Operations**
   - Add items to the cart.
   - Remove items from the cart.
   - Edit item quantities.
   - View all items in the cart.

2. **Billing**
   - Display the current bill details.
   - Finalize and save bills to a file (`bills.txt`).
   - Clear the cart and free allocated memory.

3. **Item Database Management**
   - View available items.
   - Add new items to the database.

4. **Password Protection**
   - Secures access to the database with a password.
   - Allows changing the password (stored in `Encrypted.bin`).

5. **Help Menu**
   - Provides guidance on system usage.

## File Structure

- **`SuperMarket.c`**: Source code for the billing system.
- **`SM_data.txt`**: Initial item database with item codes, prices, discounts, and names.
- **`bills.txt`**: Stores finalized bills.
- **`Encrypted.bin`**: Stores the encrypted password for database access.

## How to Run

### Note:

- It works only in Windows OS
- To run on LINUX/Mac OS `replace` all `getch();` function calls with `getchar()`;

1. Compile the code using a C compiler (e.g., GCC):
   ```bash
   gcc SuperMarket.c -o SuperMarket
   ```
2. Execute the program:
   ```bash
   ./SuperMarket
   ```
3. Follow the prompts to interact with the system.

## Usage Instructions

### Main Menu
- `1`: Open the cart menu to add, remove, or edit items.
- `2`: Display the current bill.
- `. (dot)`: Finalize the bill directly.
- `3`: Cancel the bill (clear the cart).
- `4`: Open the item database management menu.
- `5`: View the help menu.

### Database Menu
- `1`: Add a new item to the database.
- `2`: View all items in the database.
- `3`: Return to the main menu.

### Password Handling
- The database menu requires a password for access.
- The default behavior is to prompt for password creation if not already set.

## Data Storage

- **`SM_data.txt`**:
  - Format: `<ItemCode> <MRP> <Discount> <Name>`
  - Example: `1 5.00 0.00 Munch`

- **`bills.txt`**:
  - Stores finalized bills, including item details and total amounts.

## Notes

- The system uses `getch()` for interactive prompts, so it may require additional setup for non-Windows environments.
- Input validation is minimal. Ensure correct data input.

## Future Improvements

- Enhance input validation and error handling.
- Implement a graphical user interface.
- Add real-time stock management.
- Encrypt sensitive data (e.g., user logins(password), database password(required to update database)).
- Forget password for database updation

## Authors

- SAI DEEKSHITH KONDA