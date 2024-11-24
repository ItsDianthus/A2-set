# Merge+Insert sort
import csv
import matplotlib.pyplot as plt

points = []
merge_random = []
merge_reversed = []
merge_almost_sorted = []

with open('A2_data_timediff_.txt', 'r', encoding='utf-8') as file:
    reader = csv.reader(file, delimiter=';')
    next(reader)
    for row in reader:
        points.append(int(row[0].strip()))
        merge_random.append(int(row[4].strip()))
        merge_reversed.append(int(row[5].strip()))
        merge_almost_sorted.append(int(row[6].strip()))

plt.plot(points, merge_random, label='Merge+Insert Random', color='b')
plt.plot(points, merge_reversed, label='Merge+Insert Reversed', color='g')
plt.plot(points, merge_almost_sorted, label='Merge+Insert Almost Sorted', color='r')

plt.xlabel('Points')
plt.ylabel('Time (ms)')
plt.title('Merge+Insert Performance Analysis')
plt.legend()
plt.grid(True)
plt.show()
