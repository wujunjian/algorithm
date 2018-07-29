#include <iostream>
#include <map>
#include <array>
#include <set>
#include <string>

using namespace std;

template<class KEY, class CON, class DOC>
class InvertedIndex {
private:
	map<CON, set<KEY>> m_FirstIndex;
	map<DOC, set<CON>> m_SecondIndex;
public:
	void init() {
		m_InvertedIndex.clear(); 
	}

	template<class... DOCS> inline
	void add(KEY key, DOCS... docs)
	{
		set<CON> con;
		string csize = to_string(sizeof...(docs));
		CON scon;
		conjunction(con, docs...);
		auto coniter = con.begin();
		for (; coniter != con.end(); ++coniter)
		{
			scon += *coniter;
		}
		m_FirstIndex[scon].insert(key);
		toconjunction(scon, csize, docs...);
	}

	template <class... DOCS> inline
	void toconjunction(CON scon, string csize, DOCS... docs)
	{
		//zero template
	}
	template <class DOC1, class... DOCS> inline
	void toconjunction(CON scon, string csize, DOC1 doc, DOCS... docs)
	{
		m_SecondIndex[csize + doc].insert(scon);
		toconjunction(scon, csize, docs...);
	}

	template <class... DOCS> inline
	void conjunction(set<CON>& con, DOCS... docs)
	{
		//zero template
	};

	template<class DOC1, class ...DOCS> inline
	void conjunction(set<CON>& con, DOC1 doc, DOCS... docs) {
		//string csize = to_string(sizeof...(docs));
		
		con.insert(doc);
		conjunction(con, docs...);
	}

	template<class ...DOCS> inline
	void querycon(set<KEY>& result, string csize, DOCS... docs) {
		//zero template
	}

	template<class DOC1, class ...DOCS> inline
	void querycon(set<KEY>& result, string csize, DOC1 doc, DOCS... docs) {
		auto msiter = m_SecondIndex.find(csize + doc);
		if (msiter != m_SecondIndex.end())
		{
			if (result.empty())
			{
				result = msiter->second;
			}
			else {
				auto riter = result.begin();
				for (; riter != result.end();)
				{
					if (msiter->second.find(*riter) == msiter->second.end())
						riter = result.erase(riter);
					else
						++riter;
				}
			}
		}
		else {
			result.clear();
			return; //需要取交集,所以一旦有查询为空的,则直接返回.
		}
		querycon(result, csize, docs...);
	}


	template<class ...DOCS> inline
	void get(set<KEY>& result, DOCS... docs)
	{
		int nsize = sizeof...(docs);
		for (; nsize >= 0; --nsize)
		{
			set<CON> cons;
			set<KEY> keys;
			string csize = to_string(nsize);
			querycon(cons, csize, docs...);
			querykey(cons, keys);
			
			auto k = keys.begin();
			for (; k != keys.end(); ++k)
			{
				result.insert(*k);
			}
		}
	}

    inline
	void querykey(set<CON>& cons, set<KEY>& result) {
		auto con = cons.begin();
		for (; con != cons.end(); ++con)
		{
			auto mFiiter = m_FirstIndex.find(*con);
			if (mFiiter != m_FirstIndex.end())
			{
				if (result.empty())
				{
					result = mFiiter->second;
				}
				else
				{
					// result.merge()  c++17
					auto i = mFiiter->second.begin();
					for (; i != mFiiter->second.end(); ++i)
					{
						result.insert(*i);
					}
				}
			}
			else {
				throw;//TODO
			}
		}
	}
};

int main() {
	InvertedIndex<string, string, string> II;
	II.add("KEY0", "DOC1", "DOC2", "DOC3");
	II.add("KEY1", "DOC4", "DOC2", "DOC66");
	II.add("KEY2", "zhongguo", "shanxi", "taiyuan");
	II.add("KEY3", "dalian", "caohu", "anhui");
	II.add("KEY4", "dalian", "DOC66", "anhui");
	II.add("KEY5", "DOC2", "anhui");
	II.add("KEY5", "DOC2", "anhui");

	set<string> result;
	II.get(result, "DOC2", "anhui");

	for (auto i = result.begin(); i != result.end(); ++i)
	{
		cout << "key:" << *i << ":" << endl;
	}
	return 0;
}