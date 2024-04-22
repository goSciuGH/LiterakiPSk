#include "Dictionary.h"
#include "GameEngine.h"

#include <iostream>
#include <mutex>

void Dictionary::loadDictionary(const std::string& filename, bool& dictLoaded)
{
	loadingThread = std::thread(&Dictionary::loadIntoTrie, this, filename, std::ref(dictLoaded));
}

void Dictionary::waitForLoading()
{
	if (loadingThread.joinable())
	{
		loadingThread.join();
	}
}

bool Dictionary::searchWord(const std::wstring& word) const
{
	TrieNode* node = root;

	for (wchar_t ch : word)
	{
		if (node->children.find(ch) == node->children.end())
		{
			return false;
		}

		node = node->children[ch];
	}

	return node->isEndOfWord;
}

void Dictionary::insertWordsBatch(const std::vector<std::wstring>&& words)
{
	std::lock_guard<std::mutex> lock(trieMutex);

	for (const auto& word : words)
	{
		insertWord(root, word);
	}
}

void Dictionary::insertWord(TrieNode* node, const std::wstring& word)
{
	for (wchar_t ch : word)
	{
		if (node->children.find(ch) == node->children.end())
		{
			node->children[ch] = new TrieNode();
		}

		node = node->children[ch];
	}

	node->isEndOfWord = true;
}

void Dictionary::loadIntoTrie(const std::string& filename, bool& dictLoaded)
{
	std::wifstream file(filename);

	if (file.is_open())
	{
		std::wstring word;
		std::vector<std::wstring> wordsBatch;
		const int batchSize = 1000;

		while (file >> word)
		{
			wordsBatch.push_back(word);

			if (wordsBatch.size() >= batchSize)
			{
				std::thread batchThread(&Dictionary::insertWordsBatch, this, std::move(wordsBatch));
				batchThread.detach();
				wordsBatch.clear();
			}
		}

		if (!wordsBatch.empty())
		{
			std::thread batchThread(&Dictionary::insertWordsBatch, this, std::move(wordsBatch));
			batchThread.detach();
			wordsBatch.clear();
		}

		file.close();
	}
	else
	{
		std::cerr << "Unable to load dictionary" << std::endl;
	}

	dictLoaded = true;
	std::cout << "Done! " << std::endl;
	engine->gameState = 1;
}

void Dictionary::deleteTrie(TrieNode* node)
{
	for (auto& pair : node->children)
	{
		deleteTrie(pair.second);
	}

	delete node;
}
