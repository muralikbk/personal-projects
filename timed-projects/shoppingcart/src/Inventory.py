import json

class InventoryItem:
    def __init__(self, inCode, inName, inPrice):
        self.Code = inCode
        self.Name = inName
        temp_Price = inPrice
        temp_Price = temp_Price.replace(',','')
        temp_Price = temp_Price.replace('€','')
        self.Price = float(temp_Price)

    def __repr__(self):
        return "<InventoryItem Code:%s, Name:%s, Price:{%.2f}€>" %( self.Code, self.Name, self.Price )
    
    def __str__(self):
        return "{ <InventoryItem> Code:%s, Name:%s, Price:{%.2f}€ }" %( self.Code, self.Name, self.Price )


class Inventory:
    def __init__(self, filename):
        with open(filename, "r") as in_file:
            raw_data = in_file.read()
        self.InventoryList = dict()
        json_obj = json.loads(raw_data)
        for obj in json_obj:
            item = InventoryItem(obj["Code"], obj["Name"], obj["Price"])
            self.InventoryList[obj["Code"].upper()] = item
        
    def __repr__(self):
        str_rep = "<Inventory\n"
        for item in self.InventoryList:
            str_rep += repr(item) + ":" + repr(self.InventoryList[item]) + "\n"
        return str_rep + ">"

    def __str__(self):
        str_rep = "{<Inventory>[\n"
        for item in self.InventoryList:
            str_rep += str(item) + ":" + str(self.InventoryList[item]) + "\n"
        return str_rep + "]}"


#Test for the Inventory class
def run_tests(filename):
    inv = Inventory(filename)
    print(inv)

if __name__ == "__main__":
    import sys
    if(len(sys.argv) != 2):
        print("Usage is " + sys.argv[0] + " <filename>")
    else:
        run_tests(sys.argv[1])




