﻿// heap.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include <vector>

typedef unsigned int u32;

// this is minimum heap
template <typename T>
class heap {
	std::vector <T> heap_data;

public:
	heap() {}
	~heap() {}

private:
	const u32 get_left_child(const u32 parent_idx) const {
		return (parent_idx * 2 + 1);
	}

	const u32 get_right_child(const u32 parent_idx) const {
		return (parent_idx * 2 + 2);
	}

	const u32 get_parent(const u32 idx) const {
		return idx > 0? (idx - 1) / 2 : 0;
	}

public:
	void insert(const T &data) {
		heap_data.push_back(data);

		if (heap_data.size() == 1)
			return;

		u32 data_index = heap_data.size() - 1;
		
		while (true) {
			u32 parent_idx = get_parent(data_index);

			if (heap_data[data_index] < heap_data[parent_idx]) {
				std::swap(heap_data[data_index], heap_data[parent_idx]);
				data_index = parent_idx;
			} else
				break;
		}
	}

	bool delete_el(const T &data) {
		u32 i = 0;

		u32 size = heap_data.size();

		while (i < size) {
			if (heap_data[i] == data)
				break;

			++i;
		}

		if (i == size)
			return false;

		std::swap(heap_data[i], heap_data[size - 1]);
		u32 smallest_idx = i;

		do {
			u32 cur_idx = smallest_idx;
			u32 left_child = get_left_child(cur_idx);
			u32 right_child = get_right_child(cur_idx);

			bool has_left = left_child < size;
			bool has_right = right_child < size;

			if (has_left && has_right) {
				if (heap_data[cur_idx] < heap_data[left_child] && heap_data[cur_idx] < heap_data[right_child])
					break;

				smallest_idx = (heap_data[left_child] < heap_data[right_child]) ? left_child : right_child;
			} else if (has_left) {
				if (heap_data[cur_idx] < heap_data[left_child])
					break;

				smallest_idx = left_child;
			} else
				break;

			if (cur_idx == smallest_idx)
				break;

			std::swap(heap_data[cur_idx], heap_data[smallest_idx]);
		} while(true);

		heap_data.erase(heap_data.begin() + (size - 1));

		return true;
	}

	void print_heap() {
		for (u32 i = 0, size = heap_data.size(); i < size; ++ i)
			std::cout << heap_data[i] << " ";

		std::cout << std::endl;
	}
};

int main()
{
	heap<int> *h = new heap<int>();

	h->insert(3);
	h->insert(4);
	h->insert(0);
	h->insert(1);
	h->insert(2);
	h->insert(7);
	h->insert(8);
	h->insert(-1);

	h->print_heap();

	h->delete_el(4);
	h->delete_el(0);
	h->delete_el(-4);
	//h->delete_el(1);
	//h->delete_el(2);
	//h->delete_el(7);
	//h->delete_el(8);

	h->print_heap();

	delete h;
    return 0;
}

внешне структура данных напоминает бинарное дерево, только располагается в массиве.
бывает max и min 
при max у root ежит максимальный элемент. Все значения элементов, которые располагаются ниже родительского элемента, должны быть меньше чем родительский элемент.

			0
		1		2
	3		4 5		6
7	  8

left child получаем по формуле - (cur_index * 2) + 1;
right child - 					 (cur_index * 2) + 2;

parent 							- (child_idx - 1) / 2;

запоминать ничего не нужно, все высчитывается чисто математически.



если добавляем  кучу - добавляем на последнее место, и дальше сравниваем с родительским элементом

если удаляем элемент - находим нужный элемент, меняем его местами с последним элементом, сравниваем с чисдренами и ставим на нужное место. - удаляем последний элемент.


