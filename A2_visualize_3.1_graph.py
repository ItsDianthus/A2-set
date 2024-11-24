import csv
import matplotlib.pyplot as plt

points = []
merge_random = []
merge_reversed = []
merge_almost_sorted = []

with open('data.txt', 'r', encoding='utf-8') as file:
    reader = csv.reader(file, delimiter=';')
    next(reader)
    for row in reader:
        points.append(int(row[0].strip()))
        merge_random.append(int(row[1].strip()))
        merge_reversed.append(int(row[2].strip()))
        merge_almost_sorted.append(int(row[3].strip()))

plt.plot(points, merge_random, label='Merge Random', color='b')
plt.plot(points, merge_reversed, label='Merge Reversed', color='g')
plt.plot(points, merge_almost_sorted, label='Merge Almost Sorted', color='r')

plt.xlabel('Points')
plt.ylabel('Time (ms)')
plt.title('Merge Performance Analysis')
plt.legend()
plt.grid(True)
plt.show()
