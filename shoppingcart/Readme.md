Project Requirements in the ProjectRequirements.md file.
Project is coded in Python 3 on Ubuntu 19.10 (Linux).


Assumptions:
I am making the following assumptions :
1) The list of products with prices as well as the checkout list will be input as file of particular format which will be added in Readme of the program.
2) Item list (shopping cart) will be input as comma separated list. The program will take user input, output the total value and then wait for further input.
3) I am dealing with only one currency - Euros.
4) The inputs provided will be valid. There is only basic input sanitization.
5) The list of products will not be changed once the program is running. If the list does change, the new values will only be reflected if the program is restarted.
6) I am assuming that the correct number of items for promotions will be provided.

    

Project structure:
The project is divided into the following modules:
1) Inventory:
    This module reads the inventory from the file, parses it and stores the data in a map for easy retrieval.
    - We are assuming correct inputs. Incorrect inputs will be ignored (e.g. invalid/negative prices).
    - Prices will a string of the format "<euros>.<cents>€".
    - If multiple items with the same code are present, the last entry will be used

2) Checkout:
    Gets an instance of inventory (above) along with the list of items in a comma separated string and creates a list of inventory items.
    If an entry not present in the Inventory, it will be ignored.
    This is where promotions will be applied. This takes the instance of shopping cart from below and applies
    any promotions as necessary.
    Uses Inventory and Shopping Cart to calculate the final total.

3) Main:
    Initializes the required components and provides interactivity for the program. 
    Reads input line by line - each line being a comma separated list of items. Then prints the final price of the shopping cart.
    The program keeps reading inputs till it reads "quit".
    Input and item inputs are case insensitive.

Run the project using the command ./run_shoppingcart.sh