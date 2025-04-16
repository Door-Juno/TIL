class Node:
    def __init__(self, data, link=None):
        self.data = data
        self.link = link

class LinkedSet:
    def __init__(self):
        self.head = None

    def contains(self, data):
        node = self.head
        while node:
            if node.data == data:
                return True
            node = node.link
        return False

    def add(self, data):
        if not self.contains(data):
            self.head = Node(data, self.head)

    def remove(self, data):
        prev, node = None, self.head
        while node:
            if node.data == data:
                if prev:
                    prev.link = node.link
                else:
                    self.head = node.link
                return
            prev = node
            node = node.link
