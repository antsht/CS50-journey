class Jar:

    def __init__(self, capacity=12):
        self._capacity = capacity
        self._size = 0

    def __str__(self):
        return "🍪" * self._size

    def deposit(self, n):
        if n > 0 and n + self._size <= self._capacity:
            self._size += n
        else:
            raise ValueError

    def withdraw(self, n):
        if n > 0 and n < self._size:
            self._size -= n
        else:
            raise ValueError

    @property
    def capacity(self):
        return self._capacity

    @property
    def size(self):
        return self._size

def main():
    jar = Jar(7)
    print(str(jar.capacity))
    jar.deposit(5)
    print(str(jar))


main()
