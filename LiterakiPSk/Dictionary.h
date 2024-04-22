#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <thread>
#include <mutex>

class GameEngine;

/// @brief Klasa reprezentuj¹ca s³ownik
class Dictionary
{
public:
	/// @brief Konstruktor domyœlny
	Dictionary(): root(new TrieNode) {}

	/// @brief Dekonstruktor
	~Dictionary() { deleteTrie(root); }

	/// @brief W³¹cza w¹tek ³adowania do s³ownika
	/// @param filename Nazwa pliku
	/// @param dictLoaded Flaga za³adowania s³ownika
	void loadDictionary(const std::string& filename, bool& dictLoaded);

	/// @brief Oczekiwanie na zakoñczenie wczytywania
	void waitForLoading();
	/// @brief Sprawdzenie czy s³owo istnieje w s³owniku
	/// @param word Wyszukiwane s³owo
	/// @return Flaga odnalezienia s³owa
	bool searchWord(const std::wstring& word) const;

	/// @brief WskaŸnik na obiekt silnika
	GameEngine* engine;

private:
	/// @brief Wêze³ drzewa Trie s³ownika
	struct TrieNode {
		std::unordered_map<wchar_t, TrieNode*> children;	///< WskaŸniki na wêz³y-potomków
		bool isEndOfWord;	///< Flaga koñca s³owa

		/// @brief Konstruktor domyœlny
		TrieNode() : isEndOfWord(false) {}
	};

	TrieNode* root;	///< Korzeñ drzewa Trie s³ownika
	std::thread loadingThread;	///< W¹tek ³adowania
	std::mutex trieMutex;	///< Muteks zabezpieczaj¹cy s³ownik
	
	/// @brief Dodaje partiê s³ów do drzewa
	/// @param words Vector s³ów
	void insertWordsBatch(const std::vector<std::wstring>&& words);
	/// @brief Dodaje s³owo do drzewa
	/// @param node Wêze³ startowy
	/// @param word S³owo do dodania
	void insertWord(TrieNode* node, const std::wstring& word);
	/// @brief Za³adowanie s³ownika z pliku
	/// @param filename 
	/// @param dictLoaded 
	void loadIntoTrie(const std::string& filename, bool& dictLoaded);
	/// @brief Usuwanie drzewa
	/// @param node Wêze³ do usuniêcia
	void deleteTrie(TrieNode* node);
};

