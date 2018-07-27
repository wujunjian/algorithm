#include <iostream>
#include <map>
#include <array>
#include <set>
#include <string>

using namespace std;

template<class KEY, class DOC>
class InvertedIndex {
private:
	map<DOC, set<KEY>> m_InvertedIndex;

public:
	void init() { m_InvertedIndex.clear(); }

	template <class... DOCS>
	void add(KEY key, DOCS... docs)
	{
		//zero template
	};

	template<class DOC, class ...DOCS>
	void add(KEY key, DOC doc, DOCS... docs) {
		//m_InvertedIndex[doc] = key;
		m_InvertedIndex[doc].insert(key);
		add(key, docs...);
	}

	template<class ...DOCS>
	void query(DOCS... docs) {
		//zero template
	}

	template<class DOC, class ...DOCS>
	void query(DOC doc, DOCS... docs) {
		//map<DOC, set<KEY>>::iterator iter = m_InvertedIndex.find(doc);  TODO
		auto iter = m_InvertedIndex.find(doc);
		if(iter != m_InvertedIndex.end())
			cout << iter->first << *(iter->second.begin()) << endl;

		query(docs...);
	}


};

int main() {
	InvertedIndex<string, string> II;
	II.add("KEY0", "DOC1", "DOC2", "DOC3");
	II.add("KEY1", "DOC4", "DOC2", "DOC3");

	II.query("DOC4", "DOC2");
	return 0;
}