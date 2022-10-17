import re
import string



def CountAllItems():
    source_text = open("./Input.txt", "r").read()
    recorded_items = {}
    for item in source_text.split("\n"):
        if (item in recorded_items):
            recorded_items[item] += 1
        else:
            recorded_items[item] = 1
    for item in recorded_items:
        print(item + ": " + str(recorded_items[item]))


def CountOneItem(item_to_count):
    source_text = open("./Input.txt", "r").read()
    recorded_items = {}
    items_counted = 0
    for item in source_text.split("\n"):
        if (item_to_count == item):
            items_counted += 1
    return items_counted
            
def CountAllItemsToFile():
    source_text = open("./Input.txt", "r").read()
    target_dat = open("./frequency.dat", "w")
    recorded_items = {}
    for item in source_text.split("\n"):
        if (item in recorded_items):
            recorded_items[item] += 1
        else:
            recorded_items[item] = 1
    for item in recorded_items:
        target_dat.write(item + " " + str(recorded_items[item]) + "\n")