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
	map<DOC, map<CON, bool>> m_SecondIndex;
public:
	void init() {
		m_InvertedIndex.clear(); 
	}

	template<class... DOCS> inline
	InvertedIndex& add(KEY key, DOCS... docs)
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
		return *this;
	}

	template <class... DOCS> inline
	void toconjunction(CON scon, string csize, DOCS... docs)
	{
		//zero template
	}
	template <class DOC1, class... DOCS> inline
	void toconjunction(CON scon, string csize, DOC1 doc, DOCS... docs)
	{
		m_SecondIndex[csize + doc][scon]=true;
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
	void querycon(map<CON, int>& result, string csize, DOCS... docs) {
		//zero template
	}

	template<class DOC1, class ...DOCS> inline
	void querycon(map<CON, int>& result, string csize, DOC1 doc, DOCS... docs) {
		auto msiter = m_SecondIndex.find(csize + doc);
		if (msiter != m_SecondIndex.end())
		{
			auto ibelong = msiter->second.begin();
			for (; ibelong != msiter->second.end(); ++ibelong)
			{
				if (result.find(ibelong->first)==result.end())
				{
					result[ibelong->first] = 0;
				}

				if (ibelong->second) //belong
				{
					++result[ibelong->first];
				}
				else  //Does not belong
				{
					--result[ibelong->first];
				}
			}
		}
		querycon(result, csize, docs...);
	}


	template<class ...DOCS> inline
	void get(set<KEY>& result, DOCS... docs)
	{
		int nsize = sizeof...(docs);
		for (; nsize >= 0; --nsize)
		{
			map<CON, int> cons;
			set<KEY> keys;
			string csize = to_string(nsize);
			querycon(cons, csize, docs...);
			for (auto consiter = cons.begin(); consiter != cons.end();)
			{
				if (consiter->second != nsize)
					consiter = cons.erase(consiter);
				else
					++consiter;
			}
			querykey(cons, keys);
			
			auto k = keys.begin();
			for (; k != keys.end(); ++k)
			{
				result.insert(*k);
			}
		}
	}

    inline
	void querykey(map<CON, int>& cons, set<KEY>& result) {
		auto con = cons.begin();
		for (; con != cons.end(); ++con)
		{
			auto mFiiter = m_FirstIndex.find(con->first);
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
	II.add("TESTKEY", "zhongguo", "shanxi").add("TESTKEY2", "shanxi", "taiyuan");

	set<string> result;
	II.get(result, "DOC2", "anhui", "nothing", "DOC4", "DOC66");

	for (auto i = result.begin(); i != result.end(); ++i)
	{
		cout << "key:" << *i << ":" << endl;
	}
	return 0;
}