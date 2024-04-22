#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <thread>
#include <mutex>

class GameEngine;

/// @brief Klasa reprezentuj�ca s�ownik
class Dictionary
{
public:
	/// @brief Konstruktor domy�lny
	Dictionary(): root(new TrieNode) {}

	/// @brief Dekonstruktor
	~Dictionary() { deleteTrie(root); }

	/// @brief W��cza w�tek �adowania do s�ownika
	/// @param filename Nazwa pliku
	/// @param dictLoaded Flaga za�adowania s�ownika
	void loadDictionary(const std::string& filename, bool& dictLoaded);

	/// @brief Oczekiwanie na zako�czenie wczytywania
	void waitForLoading();
	/// @brief Sprawdzenie czy s�owo istnieje w s�owniku
	/// @param word Wyszukiwane s�owo
	/// @return Flaga odnalezienia s�owa
	bool searchWord(const std::wstring& word) const;

	/// @brief Wska�nik na obiekt silnika
	GameEngine* engine;

private:
	/// @brief W�ze� drzewa Trie s�ownika
	struct TrieNode {
		std::unordered_map<wchar_t, TrieNode*> children;	///< Wska�niki na w�z�y-potomk�w
		bool isEndOfWord;	///< Flaga ko�ca s�owa

		/// @brief Konstruktor domy�lny
		TrieNode() : isEndOfWord(false) {}
	};

	TrieNode* root;	///< Korze� drzewa Trie s�ownika
	std::thread loadingThread;	///< W�tek �adowania
	std::mutex trieMutex;	///< Muteks zabezpieczaj�cy s�ownik
	
	/// @brief Dodaje parti� s��w do drzewa
	/// @param words Vector s��w
	void insertWordsBatch(const std::vector<std::wstring>&& words);
	/// @brief Dodaje s�owo do drzewa
	/// @param node W�ze� startowy
	/// @param word S�owo do dodania
	void insertWord(TrieNode* node, const std::wstring& word);
	/// @brief Za�adowanie s�ownika z pliku
	/// @param filename 
	/// @param dictLoaded 
	void loadIntoTrie(const std::string& filename, bool& dictLoaded);
	/// @brief Usuwanie drzewa
	/// @param node W�ze� do usuni�cia
	void deleteTrie(TrieNode* node);
};

