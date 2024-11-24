#include <algorithm>
#include <chrono>
#include <fstream>
#include <iostream>
#include <random>
#include <vector>

class ArrayGenerator {
public:
  static std::vector<int> generateRandomArray(int size) {
    std::vector<int> arr(size);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 6000);

    for (int i = 0; i < size; ++i) {
      arr[i] = dis(gen);
    }
    return arr;
  }

  static std::vector<int> generateReverseSortedArray(int size) {
    std::vector<int> arr(size);
    for (int i = 0; i < size; ++i) {
      arr[i] = size - i;
    }
    return arr;
  }

  static std::vector<int> generateAlmostSortedArray(int size) {
    std::vector<int> arr = generateSortedArray(size);
    int swaps = std::min(10, size / 15);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, size - 1);

    for (int i = 0; i < swaps; ++i) {
      int idx1 = dis(gen);
      int idx2 = dis(gen);
      std::swap(arr[idx1], arr[idx2]);
    }
    return arr;
  }

  static std::vector<int> generateSortedArray(int size) {
    std::vector<int> arr(size);
    for (int i = 0; i < size; ++i) {
      arr[i] = i;
    }
    return arr;
  }

  static std::vector<int> generateSubArray(const std::vector<int> &arr,
                                           int size_arr) {
    int size = std::min(static_cast<int>(arr.size()), size_arr);
    return std::vector<int>(arr.begin(), arr.begin() + size);
  }
};

void insertionSort(std::vector<int> &arr, int l, int r) {
  for (int i = l + 1; i <= r; i++) {
    int pivot = arr[i];
    int j = i - 1;

    while (arr[j] > pivot && j >= l) {
      arr[j + 1] = arr[j];
      j--;
    }

    arr[j + 1] = pivot;
  }
}

void mergeIteration(std::vector<int> &arr, int left, int mid, int right) {
  int leftSize = mid - left + 1;
  int rightSize = right - mid;

  std::vector<int> leftArray(leftSize), rightArray(rightSize);

  for (int i = 0; i < leftSize; i++)
    leftArray[i] = arr[left + i];
  for (int j = 0; j < rightSize; j++)
    rightArray[j] = arr[mid + 1 + j];

  int l = 0, r = 0, mergedIndex = left;

  while (l < leftSize && r < rightSize) {
    if (leftArray[l] <= rightArray[r]) {
      arr[mergedIndex] = leftArray[l];
      l++;
    } else {
      arr[mergedIndex] = rightArray[r];
      r++;
    }

    mergedIndex++;
  }
  while (l < leftSize) {
    arr[mergedIndex] = leftArray[l];
    l++;
    mergedIndex++;
  }
  while (r < rightSize) {
    arr[mergedIndex] = rightArray[r];
    r++;
    mergedIndex++;
  }
}

void mergeSort(std::vector<int> &arr, int l, int r) {
  if (l < r) {
    int mid = l + (r - l) / 2;
    mergeSort(arr, l, mid);
    mergeSort(arr, mid + 1, r);
    mergeIteration(arr, l, mid, r);
  }
}

void mergeInsertionSort(std::vector<int> &arr, int l, int r,
                        int threshold_sort = 15) {
  if (r - l + 1 <= threshold_sort) {
    insertionSort(arr, l, r);
    return;
  }
  mergeSort(arr, l, r);
}

class SortTester {
public:
  static int mergeInsertionTester(std::vector<int> &arr, int thres = 15) {
    auto start = std::chrono::high_resolution_clock::now();
    mergeInsertionSort(arr, 0, arr.size() - 1, thres);
    auto elapsed = std::chrono::high_resolution_clock::now() - start;
    int msec =
        std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count();

    return msec;
  }

  static int mergeTester(std::vector<int> &arr) {
    auto start = std::chrono::high_resolution_clock::now();
    mergeSort(arr, 0, arr.size() - 1);
    auto elapsed = std::chrono::high_resolution_clock::now() - start;
    int msec =
        std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count();
    return msec;
  }
};

void createFirstDataFile() {
  

  std::ofstream outputFile("A2_data_threshold_finder.txt");

  outputFile << "Points; Threshold num; Merge+Insert random (msecs); "
                "Merge+Insert reversed (msecs); "
                "Merge+Insert almost sorted (msecs); \n";



  for (int thres = 10; thres <= 300; thres += 10) {
    int n = 10000;
    std::vector<int> randomArr = ArrayGenerator::generateRandomArray(n);
    std::vector<int> reverseSortedArr =
        ArrayGenerator::generateReverseSortedArray(n);
    std::vector<int> almostSortedArr =
        ArrayGenerator::generateAlmostSortedArray(n);

    long long mergeInsertTime1Sum = 0;
    long long mergeInsertTime2Sum = 0;
    long long mergeInsertTime3Sum = 0;
    int numTests = 2;

    // Создаем 5 массивов и записываем средние значения времени
    for (int i = 0; i < numTests; ++i) {


      int mergeInsert_time_1 =
          SortTester::mergeInsertionTester(randomArr, thres);
      int mergeInsert_time_2 =
          SortTester::mergeInsertionTester(reverseSortedArr, thres);
      int mergeInsert_time_3 =
          SortTester::mergeInsertionTester(almostSortedArr, thres);

      mergeInsertTime1Sum += mergeInsert_time_1;
      mergeInsertTime2Sum += mergeInsert_time_2;
      mergeInsertTime3Sum += mergeInsert_time_3;
    }

    // Вычисляем среднее время для каждого массива
    long long averageMergeInsertTime1 = mergeInsertTime1Sum / numTests;
    long long averageMergeInsertTime2 = mergeInsertTime2Sum / numTests;
    long long averageMergeInsertTime3 = mergeInsertTime3Sum / numTests;

    // Записываем результат в файл
    outputFile << "10000; " << thres << "; " << averageMergeInsertTime1
               << "; " << averageMergeInsertTime2 << "; "
               << averageMergeInsertTime3 << ";\n";
  }
}

void createSecondDataFile() {
  int n = 10000;
  std::vector<int> randomArr = ArrayGenerator::generateRandomArray(n);
  std::vector<int> reverseSortedArr =
      ArrayGenerator::generateReverseSortedArray(n);
  std::vector<int> almostSortedArr =
      ArrayGenerator::generateAlmostSortedArray(n);

  std::ofstream outputFile("A2_data_timediff.txt");

  outputFile << "Points; Merge random (msecs); Merge reversed (msecs); Merge "
                "almost sorted (msecs); "
                "Merge+Insert random (msecs); Merge+Insert reversed (msecs); "
                "Merge+Insert almost sorted (msecs); \n";

  for (long points = 100; points <= 10000; points += 500) {
    std::vector<int> randomSubArr =
        ArrayGenerator::generateSubArray(randomArr, points);
    std::vector<int> reverseSubArr =
        ArrayGenerator::generateSubArray(reverseSortedArr, points);
    std::vector<int> almSortedSubArr =
        ArrayGenerator::generateSubArray(almostSortedArr, points);

    int merge_time_1 = SortTester::mergeTester(randomSubArr);
    int merge_time_2 = SortTester::mergeTester(reverseSubArr);
    int merge_time_3 = SortTester::mergeTester(almSortedSubArr);

    int mergeInsert_time_1 = SortTester::mergeInsertionTester(randomSubArr);
    int mergeInsert_time_2 = SortTester::mergeInsertionTester(reverseSubArr);
    int mergeInsert_time_3 = SortTester::mergeInsertionTester(almSortedSubArr);

    outputFile << points << "; " << merge_time_1 << "; " << merge_time_2 << "; "
               << merge_time_3 << "; " << mergeInsert_time_1 << "; "
               << mergeInsert_time_2 << "; " << mergeInsert_time_3 << ";\n";
  }
}

int main() {
  //createFirstDataFile();
  createSecondDataFile();
  return 0;
}
