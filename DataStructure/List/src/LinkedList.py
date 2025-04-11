class Node:
    def __init__(self, data, link=None):
        self.data = data
        self.link = link

class LinkedList:
    def __init__(self):
        self.head = None

    def isEmpty(self):
        return self.head is None

    def insert(self, pos, data):
        new_node = Node(data)
        if pos == 0:
            new_node.link = self.head
            self.head = new_node
        else:
            prev = self.getNode(pos - 1)
            new_node.link = prev.link
            prev.link = new_node

    def delete(self, pos):
        if pos == 0:
            self.head = self.head.link
        else:
            prev = self.getNode(pos - 1)
            prev.link = prev.link.link

    def getNode(self, pos):
        node = self.head
        for _ in range(pos):
            node = node.link
        return node

    def print_list(self):
        node = self.head
        while node:
            print(node.data, end=" -> ")
            node = node.link
        print("None")