#include <iostream>
#include <map>
#include <array>
#include <set>
#include <string>
#include <time.h>
#include <thread>

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
	InvertedIndex& add(KEY key, set<DOC>&&exclude, DOCS... docs)
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
		toconjunction(scon, csize, std::forward<set<DOC>>(exclude));
		toconjunction(scon, csize, docs...);
		return *this;
	}

	inline
	void toconjunction(CON& scon, string csize, set<DOC>&& exclude)
	{
		for (auto exiter = exclude.begin(); exiter != exclude.end(); ++exiter)
		{
			m_SecondIndex[csize + *exiter][scon] = false;
		}
	}

	template <class... DOCS> inline
	void toconjunction(CON& scon, string csize, DOCS... docs)
	{
		//zero template
	}
	template <class DOC1, class... DOCS> inline
	void toconjunction(CON& scon, string csize, DOC1 doc, DOCS... docs)
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
	II.add("KEY0", set<string>{}, "DOC1", "DOC2", "DOC3");
	II.add("KEY1", set<string>{"anhui"}, "DOC4", "DOC2", "DOC66");
	II.add("KEY2", set<string>{"DOC4"}, "zhongguo", "shanxi", "taiyuan");
	II.add("KEY3", set<string>{}, "dalian", "caohu", "anhui");

	for (int i = 0; i < 100000; ++i)
	{
		II.add("KEYNN" + to_string(i), set<string>{}, "dalian", "taiyuan", "anhui");
	}
	II.add("KEY4", set<string>{}, "dalian", "DOC66", "anhui");
	II.add("KEY5", set<string>{}, "DOC2", "anhui");
	II.add("TESTKEY", set<string>{"taiyuan"}, "zhongguo", "shanxi").add("TESTKEY", set<string>{}, "shanxi", "taiyuan");

	set<string> result;
	clock_t begin = clock();
	//this_thread::sleep_for(2s);
	std::chrono::milliseconds ms(1);
	this_thread::sleep_for(ms);
	//this_thread::sleep_for(std::chrono::milliseconds(2));
	//this_thread::sleep_for(std::chrono::milliseconds{ 2 });
	II.get(result, "zhongguo", "anhui", "taiyuan", "dalian", "DOC66");
	clock_t end = clock();
	double  dur = 1000* (end - begin)/ CLOCKS_PER_SEC;
	printf("CPU time used (per clock(): %.3f ms\n", dur);

	for (auto i = result.begin(); i != result.end(); ++i)
	{
		cout << "key:" << *i << ":" << endl;
	}
	return 0;
}