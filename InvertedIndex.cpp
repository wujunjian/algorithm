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
	map<DOC, set<KEY>> m_ExcludeIndex;
	set<KEY> m_EmptyDoc;
public:
	void init() {
		m_InvertedIndex.clear(); 
		m_ExcludeIndex.clear();
	}

	void add(KEY key)
	{
		m_EmptyDoc.insert(key);
	}

	template <class... DOCS>
	void add(KEY key, DOCS... docs)
	{
		//zero template
	};

	template<class DOC1, class ...DOCS>
	void add(KEY key, DOC1 doc, DOCS... docs) {
		//m_InvertedIndex[doc] = key;
		m_InvertedIndex[doc].insert(key);
		add(key, docs...);
	}

	template<class ...DOCS>
	void query(map<KEY, set<DOC>>& result, DOCS... docs) {
		//zero template
	}

	template<class DOC1, class ...DOCS>
	void query(map<KEY, set<DOC>>& result, DOC1 doc, DOCS... docs) {
		//map<DOC, set<KEY>>::iterator iter = m_InvertedIndex.find(doc);  TODO
		auto miiiter = m_InvertedIndex.find(doc);
		if(miiiter != m_InvertedIndex.end())
			//cout << iter->first << *(iter->second.begin()) << endl;
			for (auto iiter = miiiter->second.begin(); iiter != miiiter->second.end(); ++iiter)
			{
				auto existkey = result.find(*iiter);
				if (existkey != result.end())
				{
					result[*iiter].insert(doc);
				}
				else {
					result[*iiter] = set<DOC>{ doc };
				}
			}

		//if(sizeof...(docs)>0)
		query(result, docs...);
	}

	template<class DOC1, class ...DOCS>
	void exclude(KEY key, DOC1 doc, DOCS... docs)
	{
		m_ExcludeIndex[doc].insert(key);
		exclude(key, docs...);
	}
	template<class ...DOCS>
	void exclude(KEY key, DOCS... docs)
	{
		//zero template
	}

	template<class ...DOCS>
	void queryexclude(map<KEY, set<DOC>>& result, DOCS... docs) {
		//zero template
	}

	template<class DOC1, class ...DOCS>
	void queryexclude(map<KEY, set<DOC>>& result, DOC1 doc, DOCS... docs) {

		auto miiiter = m_ExcludeIndex.find(doc);
		if (miiiter != m_ExcludeIndex.end())
			//cout << iter->first << *(iter->second.begin()) << endl;
			for (auto iiter = miiiter->second.begin(); iiter != miiiter->second.end(); ++iiter)
			{
				auto existkey = result.find(*iiter);
				if (existkey != result.end())
				{
					result.erase(existkey);
				}
			}
		queryexclude(result, docs...);
	}

	template<class... DOCS>
	void queryfinal(map<KEY, set<DOC>>& result, DOCS... docs)
	{
		query(result, docs...);
		queryexclude(result, docs...);
	}
};

int main() {
	InvertedIndex<string, string> II;
	II.add("KEY0", "DOC1", "DOC2", "DOC3");
	II.add("KEY1", "DOC4", "DOC2", "DOC66");
	II.add("KEY2", "zhongguo", "shanxi", "taiyuan");
	II.add("KEY3", "dalian", "caohu", "anhui");
	II.add("KEY4", "dalian", "DOC66", "anhui");
	II.add("KEY5", "DOC2", "anhui");
	II.add("KEY5", "DOC2", "anhui");
	II.exclude("KEY5", "DOC4");

	map<string, set<string>> result;
	II.queryfinal(result, "DOC2", "DOC4", "anhui");

	for (auto i = result.begin(); i != result.end(); ++i)
	{
		cout << "key:" << i->first << ": match doc num: " << i->second.size() << ":";
		for (auto j = i->second.begin(); j != i->second.end(); ++j)
		{
			cout << *j ;
		}
		cout << endl;
	}
	return 0;
}