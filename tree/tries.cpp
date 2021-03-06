// tries.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <map>
#include <iostream>

typedef unsigned int u32;

struct tries_node {
	std::map <char, tries_node *> children;

	bool is_end;

	tries_node() : is_end(false) {}
	tries_node(bool end) : is_end(end) {}
};

class tries {
	tries_node *root;

	void delete_nodes (tries_node *parent, const std::string &word, const u32 index, bool &need_delete) {
		if (!parent || index >= word.length())
			return;

		std::map<char, tries_node*>::iterator it = parent->children.find(word[index]);

		if (it == parent->children.end())
			return;

		if (index == word.length() - 1)
			need_delete = true;

		delete_nodes(it->second, word, index + 1, need_delete);

		tries_node *next_node = it->second;

		if (!need_delete || !next_node->is_end)
			return;

		if (next_node->children.empty()) {
			delete next_node;
			parent->children.erase(word[index]);
			parent->is_end = true;
		} else {
			next_node->is_end = false;
		}
	}

	void delete_all(tries_node *parent) {
		if (!parent)
			return;

		for(u32 i = 0; i < parent->children.size(); ++i)
			delete_all(parent->children[i]);

		delete parent;
		parent = nullptr;
	}
public:
	tries () : root(nullptr) {}

	~tries () {
		delete_all(root);	
	}

	void insert_word(const std::string &str) {
		
		if (!root)
			root = new tries_node ();

		tries_node *cur = root;

		for (u32 i = 0, size = str.length(); i < size; ++i) {
			std::map<char, tries_node*>::iterator it = cur->children.find(str[i]);

			if (it == cur->children.end()) {
				tries_node *new_node = new tries_node();
				cur->children.insert(std::pair<char, tries_node*>(str[i], new_node));
				cur = new_node;
			} else {
				cur = it->second;
			}
		}

		cur->is_end = true;
	}

	void delete_word(const std::string &str) {
		bool need_delete = false;
		delete_nodes(root, str, 0, need_delete);
	}

	bool contains(const std::string &str, bool whole_word) {
		if (!root)
			return false;

		tries_node *cur = root;

		for (u32 i = 0, size = str.length(); i < size; ++i) {
			std::map<char, tries_node*>::iterator it = cur->children.find(str[i]);

			if (it == cur->children.end()) {
				return false;
			} else {
				cur = it->second;
			}
		}

		return whole_word ? cur->is_end : true;	
	}
};

int main()
{
	tries *tr = new tries();
	tr->insert_word("abc");
	tr->insert_word("aba");
	tr->delete_word("abc");
	//tr->delete_word("aba");

	std::cout << tr->contains("abc", true) << std::endl;
	std::cout << tr->contains("aba", true) << std::endl;
	std::cout << tr->contains("ab", false) << std::endl;
	std::cout << tr->contains("cb", false) << std::endl;

	delete tr;
    return 0;
}



самое лучшее объяснение здесь
https://www.youtube.com/watch?v=AXjmTQ8LEoI


