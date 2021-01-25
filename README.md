# Word Clouds

## 1. Background
When you search for something online or when you click on an advertisement in an email you got, that action is tracked. This data is being aggregated and used to target marketing campaigns specifically catering to your history and projected interests. Companies then use data visualizations (like charts, graphs, infographics, and more) in order to communicate important information at a glance. The action of visualizing the data is something that helps us try and make sense of it.
For this project, we are going to generate the data for a simple data visualization. A word cloud is a simple type of data visualization that highlights important textual data points by analyzing the frequency of a word. Given some text, formatted in a specific way, we should be able to generate a list of all words and their frequency in the text. Then, by exporting the list, we can use one of the many online word cloud generators to visualize our data.
In Figure 1 below, a list of words generated from our proj5_test1.txt file has been visualized by removing all common words (we remove them) and all words that have frequency less than 2 (the word cloud tool removes them).

## 2. Description
### Class 1: LL<br>
This is a very important class. The project uses a linked list to hold templated pairs. The Nodes of the linked list hold a pair (T,int) meaning whatever T is and always an integer. It templated so that it could store the information about whatever it is designed to hold (our project will only hold strings) and a corresponding quantity. The LL works like a set though – everything in the LL is sorted and whatever the “T” is will always be the key. You cannot have duplicate keys in the linked list. When you insert a new node into the LL, you will need to insert it in order. Therefore, the insert function is by far the most complicated of the project. After a word is inserted into the linked list, if any additional instances of that word are found, instead of adding the word again, the quantity is increased.
You must implement the copy constructor and assignment operator in this class (even if we don’t use them for this project). See the LL.cpp file for additional details for other functions that you need to implement including remove. There should be absolutely NO references to anything about word clouds or words in this LL! 
You should implement this class by itself and then test it completely before using it. There is sample test code at the bottom of LL.cpp. You can uncomment it as you code functions to test it incrementally. Do not forget how we must implement templated classes! 

### Class 2: WordCloud<br>
For this project, a WordCloud will read in a single file and process it. The processing involves reading all words from a file and inserting them into the linked list. If a word already exists in the linked list, then the quantity of that word is increased instead of adding it again. All punctuation must be removed from the words except if the word requires additional punctuation such as a contraction. Additionally, there is a list of common words (such as “the”, “and”, or “us”) included in the WordCloud.h that needs to be removed from the word cloud. Finally, the user is asked if they would like to remove all words with a frequency of 1. If they respond with YES, Y, yes, or y all words with a frequency (quantity) of 1 are removed from the linked list.

## 3. Overview
In this project, you will:
  *	Practice basic C++ syntax including branching structures
  *	Write classes and instantiate those classes using a constructor
  *	Create a templated data structure (linked list)
  *	Implement copy constructor and assignment operators
  *	Use simple file input
  *	Use overloaded operators to access templated data structure
