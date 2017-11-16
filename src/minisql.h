#ifndef __RE_LEX_H__
#define __RE_LEX_H__

#ifdef _WIN32
#pragma warning(disable:4996)
#endif

extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

#include <vector>
#include <algorithm>
#include <functional>
#include <unordered_map>
#include <map>
using namespace std;

#include "rapidjson/document.h"
using namespace rapidjson;

#define DBTYPE_NUM 1
#define DBTYPE_STR 2
#define CHECK_VAL_NULL() \
	auto& value = val[comp.m_nIndex]; \
	if (value.IsNull()) \
		return false; \

#define CHECK_LEN()\
	if (m_nCompListLen >= COMP_LEN)\
		{\
		printf("Error addComp, len more than %d!\n", COMP_LEN);\
		return;\
		}

#define _SIMPQUERY_BODY1 \
	{ \
		m_nCompListLen = 0; \
		int count = 0; \
		auto& datas = m_doc["datas"]; \
		int len = datas.Size(); \
		for (int i = 0; i < len; ++i) \
				{ \
			auto& data = datas[i];

#define _SIMPQUERY_BODY2 \
			{ \
				count++; \
				m_vResult.push_back(i); \
			} \
				} \
	return count; \
}

#define _SIMPQUERY_BODY1_2 \
	{ \
		m_nCompListLen = 0; \
		int count = 0; \
		auto& datas = m_doc["datas"]; \
		int vVecLen = m_vecIndexResult.size();\
		int len;\
		for (int i = 0; i < vVecLen; ++i) \
		{ \
			vector<unsigned short>& vec = *m_vecIndexResult[i];\
			len = vec.size(); \
                for (int j = 0; j < len; ++j)\
			{\
				auto dataIndex = vec[j]; \
				auto& data = datas[dataIndex];

#define _SIMPQUERY_BODY2_2 \
				{ \
					count++; \
					m_vResult.push_back(dataIndex); \
				} \
			}\
		} \
	return count; \
}

#define _SIMP_FUNC int simpleQueryLoop (
#define _SIMP_FUNC2 int queryLoop (
#define _SIMP_COMP(n) comp##n.comp(comp##n, data)
#define _COMP(n) CompBase& comp##n

#define _SIMPQUERY0() _SIMP_FUNC ) _SIMPQUERY_BODY1 \
	 _SIMPQUERY_BODY2

#define _SIMPQUERY1(a) _SIMP_FUNC _COMP(1)) _SIMPQUERY_BODY1 \
	if (_SIMP_COMP(1)) _SIMPQUERY_BODY2

#define _SIMPQUERY2(a, b) _SIMP_FUNC _COMP(1), _COMP(2)) _SIMPQUERY_BODY1 \
	if (_SIMP_COMP(1) & _SIMP_COMP(2)) _SIMPQUERY_BODY2

#define _SIMPQUERY3(a, b, c) _SIMP_FUNC _COMP(1), _COMP(2), _COMP(3)) _SIMPQUERY_BODY1 \
	if (_SIMP_COMP(1) & _SIMP_COMP(2) & _SIMP_COMP(3)) _SIMPQUERY_BODY2

#define _SIMPQUERY4(a, b, c, d) _SIMP_FUNC _COMP(1), _COMP(2), _COMP(3), _COMP(4)) _SIMPQUERY_BODY1 \
	if (_SIMP_COMP(1) & _SIMP_COMP(2) & _SIMP_COMP(3) & _SIMP_COMP(4)) _SIMPQUERY_BODY2

#define _SIMPQUERY5(a, b, c, d, e) _SIMP_FUNC _COMP(1), _COMP(2), _COMP(3), _COMP(4), _COMP(5)) _SIMPQUERY_BODY1 \
	if (_SIMP_COMP(1) & _SIMP_COMP(2) & _SIMP_COMP(3) & _SIMP_COMP(4) & _SIMP_COMP(5)) _SIMPQUERY_BODY2

#define _SIMPQUERY6(a, b, c, d, e, f) _SIMP_FUNC _COMP(1), _COMP(2), _COMP(3), _COMP(4), _COMP(5), _COMP(6)) _SIMPQUERY_BODY1 \
	if (_SIMP_COMP(1) & _SIMP_COMP(2) & _SIMP_COMP(3) & _SIMP_COMP(4) & _SIMP_COMP(5) & _SIMP_COMP(6)) _SIMPQUERY_BODY2

#define _SIMPQUERY7(a, b, c, d, e, f, g) _SIMP_FUNC _COMP(1), _COMP(2), _COMP(3), _COMP(4), _COMP(5), _COMP(6), _COMP(7)) _SIMPQUERY_BODY1 \
	if (_SIMP_COMP(1) & _SIMP_COMP(2) & _SIMP_COMP(3) & _SIMP_COMP(4) & _SIMP_COMP(5) & _SIMP_COMP(6) & _SIMP_COMP(7)) _SIMPQUERY_BODY2

#define _SIMPQUERY8(a, b, c, d, e, f, g, h) _SIMP_FUNC _COMP(1), _COMP(2), _COMP(3), _COMP(4), _COMP(5), _COMP(6), _COMP(7), _COMP(8)) _SIMPQUERY_BODY1 \
	if (_SIMP_COMP(1) & _SIMP_COMP(2) & _SIMP_COMP(3) & _SIMP_COMP(4) & _SIMP_COMP(5) & _SIMP_COMP(6) & _SIMP_COMP(7) & _SIMP_COMP(8)) _SIMPQUERY_BODY2


#define _QUERY0() _SIMP_FUNC2) _SIMPQUERY_BODY1_2 \
	_SIMPQUERY_BODY2_2

#define _QUERY1(a) _SIMP_FUNC2 _COMP(1)) _SIMPQUERY_BODY1_2 \
	if (_SIMP_COMP(1)) _SIMPQUERY_BODY2_2

#define _QUERY2(a, b) _SIMP_FUNC2 _COMP(1), _COMP(2)) _SIMPQUERY_BODY1_2 \
	if (_SIMP_COMP(1) & _SIMP_COMP(2)) _SIMPQUERY_BODY2_2

#define _QUERY3(a, b, c) _SIMP_FUNC2 _COMP(1), _COMP(2), _COMP(3)) _SIMPQUERY_BODY1_2 \
	if (_SIMP_COMP(1) & _SIMP_COMP(2) & _SIMP_COMP(3)) _SIMPQUERY_BODY2_2

#define _QUERY4(a, b, c, d) _SIMP_FUNC2 _COMP(1), _COMP(2), _COMP(3), _COMP(4)) _SIMPQUERY_BODY1_2 \
	if (_SIMP_COMP(1) & _SIMP_COMP(2) & _SIMP_COMP(3) & _SIMP_COMP(4)) _SIMPQUERY_BODY2_2

#define _QUERY5(a, b, c, d, e) _SIMP_FUNC2 _COMP(1), _COMP(2), _COMP(3), _COMP(4), _COMP(5)) _SIMPQUERY_BODY1_2 \
	if (_SIMP_COMP(1) & _SIMP_COMP(2) & _SIMP_COMP(3) & _SIMP_COMP(4) & _SIMP_COMP(5)) _SIMPQUERY_BODY2_2

#define _QUERY6(a, b, c, d, e, f) _SIMP_FUNC2 _COMP(1), _COMP(2), _COMP(3), _COMP(4), _COMP(5), _COMP(6)) _SIMPQUERY_BODY1_2 \
	if (_SIMP_COMP(1) & _SIMP_COMP(2) & _SIMP_COMP(3) & _SIMP_COMP(4) & _SIMP_COMP(5) & _SIMP_COMP(6)) _SIMPQUERY_BODY2_2

#define _QUERY7(a, b, c, d, e, f, g) _SIMP_FUNC2 _COMP(1), _COMP(2), _COMP(3), _COMP(4), _COMP(5), _COMP(6), _COMP(7)) _SIMPQUERY_BODY1_2 \
	if (_SIMP_COMP(1) & _SIMP_COMP(2) & _SIMP_COMP(3) & _SIMP_COMP(4) & _SIMP_COMP(5) & _SIMP_COMP(6) & _SIMP_COMP(7)) _SIMPQUERY_BODY2_2

#define SORT_RESULT_BODY1 \
            	sort(m_vResult.begin(), m_vResult.end(), \
            	     [&keyIndex, &datas, &keyType](int index1, int index2) \
            	     { \
            	        auto& data1 = datas[index1][keyIndex]; \
            	        auto& data2 = datas[index2][keyIndex]; \
            	        if (data1.IsNull() || data2.IsNull()) \
            	        { \
            	            return false; \
            	        }
#define SORT_RESULT_BODY2 });

namespace RE
{
	struct StrCompare
	{
		bool operator()(const char *str1, const char *str2) const
		{
			return strcmp(str1, str2) == 0;
		}
	};

	struct HashFunc
	{
		size_t operator()(const char *str) const
		{
			unsigned int seed = 131;
			unsigned int hash = 0;
			while (*str)
			{
				hash = hash * seed + (*str++);
			}
			return hash;
		}
	};

    enum QueryError{
        errorNone = 0,              // No error.
        jsonParseError,             // rapidjson parse error.
        jsonHeadError,              // json file without head member
        jsonDatasError,             // json file without datas member
        jsonKeysError,              // json file without keys member
        indexKeyNotFound,           // key not found when gen index
        compTooMoreOrLess,                // compare condition too more
        compKeyNotFound,            // compare key not found
        compIsInvalid,              // compare is not support or invalid
        compTypeIsNotNum,           // query field type isn't 'number'
        compTypeIsNotStr,           // query field type isn't 'string'
        queryInCountError,          // query in list count must great then zero
        resultIndexError,           // get result index is invalid
        orderKeyNotFound,           // order key not found
    };

	struct CompBase;

	typedef GenericValue<UTF8<> > Item;
	typedef function<bool(CompBase&, Item&)> CompFunc;
	typedef function<void(CompBase&, vector<vector<unsigned short>* >&, void*, int&)> KeyIndexFunc;

	typedef pair<double, vector<unsigned short>* > NumKeyIndexItem;
	typedef vector<NumKeyIndexItem> NumKeyIndexVec;
	typedef unordered_map<double, vector<unsigned short>* > NumKeyIndexMap;

	typedef pair<const char*, vector<unsigned short>* > StrKeyIndexItem;
	typedef vector<StrKeyIndexItem> StrKeyIndexVec;
	typedef unordered_map<const char*, vector<unsigned short>*, HashFunc, StrCompare> StrKeyIndexMap;

	struct CompBase
	{
	public:
		const char* m_pStr;
		int m_nIndex = 0;

		bool init(int index, const char* op, double number)
		{
            m_nIndex = index;
			m_dNumber = number;
			m_eType = getNumOp(op);
			initFun();
            return m_eType != OP_TYPE_UNKNOWN;
		}

		bool init(int index, const char* op, const char* str)
        {
            m_nIndex = index;
			m_pStr = str;
			m_eType = getStrOp(op);
			initFun();
            return m_eType != OP_TYPE_UNKNOWN;
		}

		bool initBetween(int index, double a, double b)
		{
            if (a == b)
            {
                return init(index, "=", a);
            }
            m_nIndex = index;
            if (a > b)
            {
                m_dNumber = b;
                m_dMaxNumber = a;
            }
            else
            {
                m_dNumber = a;
                m_dMaxNumber = b;
            }
			m_eType = OP_TYPE_NUMBER_BT;
			initFun();
            return true;
		}

		bool initIn(int index, const double* number, int count)
		{
			if (count == 1)
			{
				return init(index, "=", number[0]);
			}
            m_nIndex = index;
            m_vecNumber.clear();
			m_vecNumber.reserve(count);
			for (int i = 0; i < count; ++i)
			{
				m_vecNumber.push_back(number[i]);
			}
			m_eType = OP_TYPE_NUMBER_IN;
			initFun();
            return true;
		}

		bool initIn(int index, const char** str, int count)
		{
			if (count == 1)
			{
				return init(index, "=", str[0]);
			}
            m_nIndex = index;
            m_vecStr.clear();
			m_vecStr.reserve(count);
			for (int i = 0; i < count; ++i)
			{
				m_vecStr.push_back(str[i]);
			}
			m_eType = OP_TYPE_STR_IN;
			initFun();
            return true;
		}

		inline void initFun()
		{
			switch (m_eType)
			{
            case OP_TYPE_NUMBER_EQ:	getKeyIndex = getKeyIndexNumberEQ;
                                    comp = compNumberEQ; break;
            case OP_TYPE_NUMBER_LT: getKeyIndex = getKeyIndexNumberLT;
                                    comp = compNumberLT; break;
            case OP_TYPE_NUMBER_GT: getKeyIndex = getKeyIndexNumberGT;
                                    comp = compNumberGT; break;
            case OP_TYPE_NUMBER_LE: getKeyIndex = getKeyIndexNumberLE;
                                    comp = compNumberLE; break;
            case OP_TYPE_NUMBER_GE: getKeyIndex = getKeyIndexNumberGE;
                                    comp = compNumberGE; break;
            case OP_TYPE_NUMBER_NE: getKeyIndex = getKeyIndexNumberNE;
                                    comp = compNumberNE; break;
            case OP_TYPE_NUMBER_BT: getKeyIndex = getKeyIndexNumberBT;
                                    comp = compNumberBT; break;
            case OP_TYPE_NUMBER_IN: getKeyIndex = getKeyIndexNumberIN;
                                    comp = compNumberIN; break;
            case OP_TYPE_STR_EQ: 	getKeyIndex = getKeyIndexStrEQ;
                                    comp = compStrEQ; break;
            case OP_TYPE_STR_LT: 	getKeyIndex = getKeyIndexStrLT;
                                    comp = compStrLT; break;
            case OP_TYPE_STR_GT: 	getKeyIndex = getKeyIndexStrGT;
                                    comp = compStrGT; break;
            case OP_TYPE_STR_LE: 	getKeyIndex = getKeyIndexStrLE;
                                    comp = compStrLE; break;
            case OP_TYPE_STR_GE: 	getKeyIndex = getKeyIndexStrGE;
                                    comp = compStrGE; break;
            case OP_TYPE_STR_NE: 	getKeyIndex = getKeyIndexStrNE;
                                    comp = compStrNE; break;
            case OP_TYPE_STR_IN: 	getKeyIndex = getKeyIndexStrIN;
                                    comp = compStrIN; break;
            default: break;
			}
		}

		inline bool getKeyIndexLen(CompBase& comp, vector<vector<unsigned short>* >& vecRes, void* p, int& len)
		{
			int oldLen = len;
			comp.m_bReturnData = false;
			getKeyIndex(comp, vecRes, p, len);
			comp.m_bReturnData = true;
			return (oldLen != len);
		}

		KeyIndexFunc getKeyIndex;
		CompFunc comp;
	private:
		#define eps 1e-5
		double m_dNumber;
		double m_dMaxNumber;
		vector<double> m_vecNumber;
		vector<const char*> m_vecStr;
		bool m_bReturnData;
		enum OP_TYPE
		{
			OP_TYPE_NUMBER_BEGIN,
			OP_TYPE_NUMBER_EQ,
			OP_TYPE_NUMBER_LT,
			OP_TYPE_NUMBER_GT,
			OP_TYPE_NUMBER_LE,
			OP_TYPE_NUMBER_GE,
			OP_TYPE_NUMBER_NE,
			OP_TYPE_NUMBER_BT,
			OP_TYPE_NUMBER_IN,

			OP_TYPE_STR_BEGIN,
			OP_TYPE_STR_EQ,
			OP_TYPE_STR_LT,
			OP_TYPE_STR_GT,
			OP_TYPE_STR_LE,
			OP_TYPE_STR_GE,
			OP_TYPE_STR_NE,
			OP_TYPE_STR_IN,

			OP_TYPE_UNKNOWN
		} m_eType;
		inline static bool compNumberEQ	(CompBase& comp, Item& val) { CHECK_VAL_NULL(); double d = value.GetDouble(); d = d - comp.m_dNumber; return (d > -eps) && (d < eps); }
		inline static bool compNumberLT (CompBase& comp, Item& val) { CHECK_VAL_NULL(); return value.GetDouble() < comp.m_dNumber; }
		inline static bool compNumberGT (CompBase& comp, Item& val) { CHECK_VAL_NULL(); return value.GetDouble() > comp.m_dNumber; }
		inline static bool compNumberLE	(CompBase& comp, Item& val) { CHECK_VAL_NULL(); return value.GetDouble() <= comp.m_dNumber; }
		inline static bool compNumberGE	(CompBase& comp, Item& val) { CHECK_VAL_NULL(); return value.GetDouble() >= comp.m_dNumber; }
		inline static bool compNumberNE	(CompBase& comp, Item& val) { CHECK_VAL_NULL(); double d = value.GetDouble(); d = d - comp.m_dNumber; return  (d < -eps) || (d > eps); }
		inline static bool compNumberBT	(CompBase& comp, Item& val) { CHECK_VAL_NULL(); double d = value.GetDouble(); return (d > comp.m_dNumber) && (d < comp.m_dMaxNumber); }
		inline static bool compStrEQ (CompBase& comp, Item& val) { CHECK_VAL_NULL(); return strcmp(value.GetString(), comp.m_pStr) == 0; }
		inline static bool compStrLT (CompBase& comp, Item& val) { CHECK_VAL_NULL(); return strcmp(value.GetString(), comp.m_pStr) <  0; }
		inline static bool compStrGT (CompBase& comp, Item& val) { CHECK_VAL_NULL(); return strcmp(value.GetString(), comp.m_pStr) >  0; }
		inline static bool compStrLE (CompBase& comp, Item& val) { CHECK_VAL_NULL(); return strcmp(value.GetString(), comp.m_pStr) <= 0; }
		inline static bool compStrGE (CompBase& comp, Item& val) { CHECK_VAL_NULL(); return strcmp(value.GetString(), comp.m_pStr) >= 0; }
		inline static bool compStrNE (CompBase& comp, Item& val) { CHECK_VAL_NULL(); return strcmp(value.GetString(), comp.m_pStr) != 0; }

		static bool compNumberIN(CompBase& comp, Item& val)
		{
			double d1 = val[comp.m_nIndex].GetDouble();
			double d2;
			int count = comp.m_vecNumber.size();
			for (int i = 0; i < count; ++i)
			{
				d2 = d1 - comp.m_vecNumber[i];
				if ((d2 > -eps) && (d2 < eps))
				{
					return true;
				}
			}
			return false;
		}

		static bool compStrIN(CompBase& comp, Item& val)
		{
			const char* str1 = val[comp.m_nIndex].GetString();
			const char* str2;
			int count = comp.m_vecStr.size();
			for (int i = 0; i < count; ++i)
			{
				str2 = comp.m_vecStr[i];
				if (strcmp(str1, str2) == 0)
				{
					return true;
				}
			}
			return false;
		}

		inline OP_TYPE getNumOp(const char* s)
		{
			if (!strcmp(s, "="))	return OP_TYPE_NUMBER_EQ;
   			if (!strcmp(s, "=="))	return OP_TYPE_NUMBER_EQ;
   			if (!strcmp(s, "<"))	return OP_TYPE_NUMBER_LT;
   			if (!strcmp(s, ">")) 	return OP_TYPE_NUMBER_GT;
   			if (!strcmp(s, "<=")) 	return OP_TYPE_NUMBER_LE;
   			if (!strcmp(s, ">=")) 	return OP_TYPE_NUMBER_GE;
   			if (!strcmp(s, "!=")) 	return OP_TYPE_NUMBER_NE;
   			printf("Error add OP_TYPE_UNKNOWN: %d, %s\n", m_nIndex, s);
   			return OP_TYPE_UNKNOWN;
		}

		inline OP_TYPE getStrOp(const char* s)
		{
			return OP_TYPE(OP_TYPE_STR_BEGIN + getNumOp(s));
		}

		inline static void checkKeyConditionsEQ(bool isOk, CompBase& comp, vector<vector<unsigned short>* >& vecRes, vector<unsigned short>& vec, int& len)
		{
			if (isOk)
			{
				auto size = vec.size();
				if (size < len)
				{
					len = size;
					if (comp.m_bReturnData)
					{
						vecRes.clear();
						vecRes.push_back(&vec);
					}
				}
			}
			else
			{
				len = 0;
			}
		}

		template<class T>
		static void checkKeyConditionsNE(int first, int last, T* pVec, CompBase& comp, 
			vector<vector<unsigned short>* >& vecRes, int& len)
		{
			int count = last - first;
			if (count > 0)
			{
				auto size = 0;
				for (int i = first; i < last; ++i)
				{
					size += (*pVec)[i].second->size();
					if (size >= len)
					{
						return ;
					}
				}
				len = size;
				if (comp.m_bReturnData)
				{
					vecRes.clear();
					vecRes.reserve(len);
					for (int i = first; i < last; ++i)
					{
						vecRes.push_back((*pVec)[i].second);
					}
				}
			}
        }

		inline static bool lowerNumCmp(const NumKeyIndexItem &p, const double& v) { return p.first < v; }
		inline static bool lowerStrCmp(const StrKeyIndexItem &p, const char* const &str) { return strcmp(p.first, str) < 0; }
		inline static bool upperNumCmp(const double& v, const NumKeyIndexItem &p) { return v < p.first; }
		inline static bool upperStrCmp(const char* const &str, const StrKeyIndexItem &p) { return strcmp(str, p.first) < 0; }

		static void getKeyIndexNumberEQ(CompBase& comp, vector<vector<unsigned short>* >& vecRes, void* p, int& len)
		{
			NumKeyIndexVec* pVec = (NumKeyIndexVec*)p;
			auto it = lower_bound(pVec->begin(), pVec->end(), comp.m_dNumber, lowerNumCmp);

			double d = it->first - comp.m_dNumber;
			checkKeyConditionsEQ((d > -eps) && (d < eps), comp, vecRes, *it->second, len);
		}

		static void getKeyIndexStrEQ(CompBase& comp, vector<vector<unsigned short>* >& vecRes, void* p, int& len)
		{
			StrKeyIndexVec* pVec = (StrKeyIndexVec*)p;
			auto it = lower_bound(pVec->begin(), pVec->end(), comp.m_pStr, lowerStrCmp);

			checkKeyConditionsEQ(strcmp(it->first, comp.m_pStr) == 0, comp, vecRes, *it->second, len);
		}

		static void getKeyIndexStrLT(CompBase& comp, vector<vector<unsigned short>* >& vecRes, void* p, int& len)
		{
			StrKeyIndexVec* pVec = (StrKeyIndexVec*)p;
			auto it = lower_bound(pVec->begin(), pVec->end(), comp.m_pStr, lowerStrCmp);
			int first = 0;
			int last = it - pVec->begin();

			checkKeyConditionsNE<StrKeyIndexVec>(first, last, pVec, comp, vecRes, len);
		}

		static void getKeyIndexNumberLT(CompBase& comp, vector<vector<unsigned short>* >& vecRes, void* p, int& len)
		{
			NumKeyIndexVec* pVec = (NumKeyIndexVec*)p;
			auto it = lower_bound(pVec->begin(), pVec->end(), comp.m_dNumber, lowerNumCmp);
			int first = 0;
			int last = it - pVec->begin();

			checkKeyConditionsNE<NumKeyIndexVec>(first, last, pVec, comp, vecRes, len);
		}

		static void getKeyIndexStrLE(CompBase& comp, vector<vector<unsigned short>* >& vecRes, void* p, int& len)
		{
			StrKeyIndexVec* pVec = (StrKeyIndexVec*)p;
			auto it = upper_bound(pVec->begin(), pVec->end(), comp.m_pStr, upperStrCmp);
			int first = 0;
			int last = it - pVec->begin();

			checkKeyConditionsNE<StrKeyIndexVec>(first, last, pVec, comp, vecRes, len);
		}

		static void getKeyIndexNumberLE(CompBase& comp, vector<vector<unsigned short>* >& vecRes, void* p, int& len)
		{
			NumKeyIndexVec* pVec = (NumKeyIndexVec*)p;
			auto it = upper_bound(pVec->begin(), pVec->end(), comp.m_dNumber, upperNumCmp);
			int first = 0;
			int last = it - pVec->begin();

			checkKeyConditionsNE<NumKeyIndexVec>(first, last, pVec, comp, vecRes, len);
		}

		static void getKeyIndexStrGT(CompBase& comp, vector<vector<unsigned short>* >& vecRes, void* p, int& len)
		{
			StrKeyIndexVec* pVec = (StrKeyIndexVec*)p;
			auto it = upper_bound(pVec->begin(), pVec->end(), comp.m_pStr, upperStrCmp);
			int first = it - pVec->begin();
			int last = pVec->size();

			checkKeyConditionsNE<StrKeyIndexVec>(first, last, pVec, comp, vecRes, len);
		}

		static void getKeyIndexNumberGT(CompBase& comp, vector<vector<unsigned short>* >& vecRes, void* p, int& len)
		{
			NumKeyIndexVec* pVec = (NumKeyIndexVec*)p;
			auto it = upper_bound(pVec->begin(), pVec->end(), comp.m_dNumber, upperNumCmp);
			int first = it - pVec->begin();
			int last = pVec->size();

			checkKeyConditionsNE<NumKeyIndexVec>(first, last, pVec, comp, vecRes, len);
		}

		static void getKeyIndexStrGE(CompBase& comp, vector<vector<unsigned short>* >& vecRes, void* p, int& len)
		{
			StrKeyIndexVec* pVec = (StrKeyIndexVec*)p;
			auto it = lower_bound(pVec->begin(), pVec->end(), comp.m_pStr, lowerStrCmp);
			int first = it - pVec->begin();
			int last = pVec->size();

			checkKeyConditionsNE<StrKeyIndexVec>(first, last, pVec, comp, vecRes, len);
		}

		static void getKeyIndexNumberGE(CompBase& comp, vector<vector<unsigned short>* >& vecRes, void* p, int& len)
		{
			NumKeyIndexVec* pVec = (NumKeyIndexVec*)p;
			auto it = lower_bound(pVec->begin(), pVec->end(), comp.m_dNumber, lowerNumCmp);
			int first = it - pVec->begin();
			int last = pVec->size();

			checkKeyConditionsNE<NumKeyIndexVec>(first, last, pVec, comp, vecRes, len);
		}

		static void getKeyIndexNumberBT(CompBase& comp, vector<vector<unsigned short>* >& vecRes, void* p, int& len)
		{
			NumKeyIndexVec* pVec = (NumKeyIndexVec*)p;
			auto it = lower_bound(pVec->begin(), pVec->end(), comp.m_dNumber, lowerNumCmp);
			int first = it - pVec->begin();
			it = upper_bound(pVec->begin(), pVec->end(), comp.m_dMaxNumber, upperNumCmp);
			int last = it - pVec->begin();

			checkKeyConditionsNE<NumKeyIndexVec>(first, last, pVec, comp, vecRes, len);
		}

		static void getKeyIndexNumberNE(CompBase& comp, vector<vector<unsigned short>* >& vecRes, void* p, int& len)
		{
		}

		static void getKeyIndexStrNE(CompBase& comp, vector<vector<unsigned short>* >& vecRes, void* p, int& len)
		{
		}

		static void getKeyIndexStrIN(CompBase& comp, vector<vector<unsigned short>* >& vecRes, void* p, int& len)
		{
			int size;
			StrKeyIndexVec* pVec = (StrKeyIndexVec*)p;
			vector<const char*> vecNumber = comp.m_vecStr;
			int vecLen = vecNumber.size();
			size = 0;
			vector<vector<unsigned short>* > vec;
			for (int i = 0; i < vecLen; ++i)
			{
				auto it = lower_bound(pVec->begin(), pVec->end(), vecNumber[i], lowerStrCmp);
				if (strcmp(it->first, vecNumber[i]) == 0)
				{
					if (comp.m_bReturnData)
					{
						vec.push_back(it->second);
					}
					size += it->second->size();
					if (size >= len)
					{
						return;
					}
				}
			}
			len = size;
			if (comp.m_bReturnData)
			{
				vecRes.clear();
				vecRes.reserve(len);
				vecLen = vec.size();
				for (int i = 0; i < vecLen; ++i)
				{
					vecRes.push_back(vec[i]);
				}
			}
		}

		static void getKeyIndexNumberIN(CompBase& comp, vector<vector<unsigned short>* >& vecRes, void* p, int& len)
		{
			int size;
			vector<pair<double, vector<unsigned short>* > >* pVec = (vector<pair<double, vector<unsigned short>* > >*)p;
			vector<double> vecNumber = comp.m_vecNumber;
			int vecLen = vecNumber.size();
			size = 0;
			vector<vector<unsigned short>* > vec;
			for (int i = 0; i < vecLen; ++i)
			{
				auto it = lower_bound(pVec->begin(), pVec->end(), vecNumber[i], lowerNumCmp);
				double d = it->first - vecNumber[i];
				if ((d>-eps) && (d<eps))
				{
					if (comp.m_bReturnData)
					{
						vec.push_back(it->second);
					}
					size += it->second->size();
					if (size >= len)
					{
						return ;
					}
				}
			}
			len = size;
			if (comp.m_bReturnData)
			{
				vecRes.clear();
				vecRes.reserve(len);
				vecLen = vec.size();
				for (int i = 0; i < vecLen; ++i)
				{
					vecRes.push_back(vec[i]);
				}
			}
		}
	};

	struct MiniSQL
	{
	private:
		#define COMP_LEN 8
		#define MAX_LEN 999999999
		Document m_doc;
		CompBase* m_pCompList[COMP_LEN];
        int m_errorCode = 0;
		int m_nCompListLen = 0;
		vector<unsigned short> m_vResult;

        map<int, void*> m_pDataMap;

		vector<vector<unsigned short>* > m_vecIndexResult;

		bool read(const char* path)
		{

			char* pData = nullptr;
			auto file = fopen(path, "rb");
			if (file == nullptr)
			{
				fputs("File error", stderr);
				exit(1);
			}
			fseek(file, 0, SEEK_END);
			int size = ftell(file);
			rewind(file);

			pData = (char*)malloc(size + 1);
			fread(pData, size, 1, file);
			pData[size] = 0;

			m_doc.Parse(pData);
			free(pData);
			if (m_doc.GetParseError())
			{
				fprintf(stderr, "JSON parse error: %d (%zu)", m_doc.GetParseError(), m_doc.GetErrorOffset());
                m_errorCode = QueryError::jsonParseError;
                return false;
			}

            if (!m_doc.HasMember("head"))
            {
                m_errorCode = QueryError::jsonHeadError;
                return false;
            }

            if (!m_doc.HasMember("datas"))
            {
                m_errorCode = QueryError::jsonDatasError;
                return false;
            }

            if (!m_doc.HasMember("keys"))
            {
                m_errorCode = QueryError::jsonKeysError;
                return false;
            }

			return true;
		}

		void* genNumberIndex(int index)
		{
			auto& datas = m_doc["datas"];
			int len = datas.Size();
			NumKeyIndexMap indexMap;
			double value = 0;

			for (int i = 0; i < len; ++i)
			{
				auto& data = datas[i];
                auto& temp = data[index];
                if (temp.IsNull())
                    continue;
                value = temp.GetDouble();
                auto it = indexMap.find(value);
				vector<unsigned short>* pVec;
				if (it == indexMap.end())
				{
					pVec = new vector<unsigned short>;
					indexMap.insert(NumKeyIndexItem(value, pVec));
					pVec->push_back(i);
				}
				else
				{
					pVec = it->second;
					pVec->push_back(i);
				}
			}

			NumKeyIndexVec* pVec = new NumKeyIndexVec();
			pVec->reserve(indexMap.size());
			for (auto it = indexMap.begin(); it != indexMap.end(); ++it)
			{
				pVec->push_back(std::move(*it));
			}
			sort(pVec->begin(), pVec->end(), [](const NumKeyIndexItem &a, const NumKeyIndexItem &b) { return a.first < b.first;});
			return pVec;
		}

		void* genStringIndex(int index)
		{
			auto& datas = m_doc["datas"];
			int len = datas.Size();
			StrKeyIndexMap indexMap;
			const char* str = nullptr;

			for (int i = 0; i < len; ++i)
			{
				auto& data = datas[i];
                auto& value = data[index];
                if (value.IsString())
                    str = value.GetString();
                else
                    str = "";
				auto it = indexMap.find(str);
				vector<unsigned short>* pVec;
				if (it == indexMap.end())
				{
					pVec = new vector<unsigned short>;
					indexMap.insert(StrKeyIndexItem(str, pVec));
					pVec->push_back(i);
				}
				else
				{
					pVec = it->second;
					pVec->push_back(i);
				}
			}
			StrKeyIndexVec* pVec = new StrKeyIndexVec;
			pVec->reserve(indexMap.size());
			for (auto it = indexMap.begin(); it != indexMap.end(); ++it)
			{
				pVec->push_back(std::move(*it));
			}
			sort(pVec->begin(), pVec->end(), [](const StrKeyIndexItem &a, const StrKeyIndexItem &b) { return strcmp(a.first, b.first) < 0;});
			return pVec;
		}

		int simpleQuery()
		{
			switch (m_nCompListLen)
			{
				case 0: return simpleQueryLoop(); break;
				case 1: return simpleQueryLoop(*m_pCompList[0]); break;
				case 2: return simpleQueryLoop(*m_pCompList[0], *m_pCompList[1]); break;
				case 3: return simpleQueryLoop(*m_pCompList[0], *m_pCompList[1], *m_pCompList[2]); break;
				case 4: return simpleQueryLoop(*m_pCompList[0], *m_pCompList[1], *m_pCompList[2], *m_pCompList[3]); break;
				case 5: return simpleQueryLoop(*m_pCompList[0], *m_pCompList[1], *m_pCompList[2], *m_pCompList[3], *m_pCompList[4]); break;
				case 6: return simpleQueryLoop(*m_pCompList[0], *m_pCompList[1], *m_pCompList[2], *m_pCompList[3], *m_pCompList[4], *m_pCompList[5]); break;
				case 7: return simpleQueryLoop(*m_pCompList[0], *m_pCompList[1], *m_pCompList[2], *m_pCompList[3], *m_pCompList[4], *m_pCompList[5], *m_pCompList[6]); break;
				case 8: return simpleQueryLoop(*m_pCompList[0], *m_pCompList[1], *m_pCompList[2], *m_pCompList[3], *m_pCompList[4], *m_pCompList[5], *m_pCompList[6], *m_pCompList[7]); break;
				default:
                    m_errorCode = QueryError::compTooMoreOrLess;
                    printf("Error CompListLen: %d\n", m_nCompListLen); m_nCompListLen = 0; break;
			}
			return 0;
		}

		_SIMPQUERY0();
		_SIMPQUERY1(1);
		_SIMPQUERY2(1, 2);
		_SIMPQUERY3(1, 2, 3);
		_SIMPQUERY4(1, 2, 3, 4);
		_SIMPQUERY5(1, 2, 3, 4, 5);
		_SIMPQUERY6(1, 2, 3, 4, 5, 6);
		_SIMPQUERY7(1, 2, 3, 4, 5, 6, 7);
		_SIMPQUERY8(1, 2, 3, 4, 5, 6, 7, 8);

		_QUERY0();
		_QUERY1(1);
		_QUERY2(1, 2);
		_QUERY3(1, 2, 3);
		_QUERY4(1, 2, 3, 4);
		_QUERY5(1, 2, 3, 4, 5);
		_QUERY6(1, 2, 3, 4, 5, 6);
		_QUERY7(1, 2, 3, 4, 5, 6, 7);

	public:
		MiniSQL(const char* path)
		{
			for (int i = 0; i < COMP_LEN; ++i)
			{
				m_pCompList[i] = new CompBase();
			}
			read(path);
		}

		void genIndex(const char* name)
		{
            auto& head = m_doc["head"];
            auto indexValue = head.FindMember(name);
            if (indexValue == head.MemberEnd())
            {
                m_errorCode = QueryError::indexKeyNotFound;
                return;
            }
			int index = indexValue->value[0].GetInt();
            if (m_pDataMap.find(index) != m_pDataMap.end())
            {
                return;
            }

			auto& datas = m_doc["datas"];
			if (datas.Size() == 0)
			{
				return;
			}

			if (indexValue->value[1].GetInt() == DBTYPE_NUM)
			{
				m_pDataMap[index] = genNumberIndex(index);
			}
			else
			{
				m_pDataMap[index] = genStringIndex(index);
			}
		}

        bool checkKeyInvalid(const char* name)
        {
            auto& head = m_doc["head"];
            if (head.FindMember(name) == head.MemberEnd())
            {
                m_errorCode = QueryError::compKeyNotFound;
                return false;
            }
            return true;
        }

        bool checkNumValue(const int type)
        {
            if (type != DBTYPE_NUM)
            {
                m_errorCode = QueryError::compTypeIsNotNum;
                return false;
            }
            return true;
        }

        bool checkStrValue(const int type)
        {
            if (type != DBTYPE_STR)
            {
                m_errorCode = QueryError::compTypeIsNotStr;
                return false;
            }
            return true;
        }

		void add(const char* name, const char* op, int number)
		{
			add(name, op, (double)number);
		}

		void add(const char* name, const char* op, double number)
		{
			CHECK_LEN();
			if (!checkKeyInvalid(name))
            {
                return;
            }

            auto& keyInfo = m_doc["head"][name];
            if (!checkNumValue(keyInfo[1].GetInt()))
            {
                return;
            }

            auto& comp = m_pCompList[m_nCompListLen];
            if (!comp->init(keyInfo[0].GetInt(), op, number))
            {
                m_errorCode = QueryError::compIsInvalid;
                return;
            }
            m_nCompListLen++;
        }

        void add(const char* name, const char* op, const char* str)
		{
			CHECK_LEN();
			if (!checkKeyInvalid(name))
            {
                return;
            }

            auto& keyInfo = m_doc["head"][name];
            if (!checkStrValue(keyInfo[1].GetInt()))
            {
                return;
            }
            auto& comp = m_pCompList[m_nCompListLen];
            if (!comp->init(keyInfo[0].GetInt(), op, str))
            {
                m_errorCode = QueryError::compIsInvalid;
                return;
            }
            m_nCompListLen++;
        }

		void addBetween(const char* name, double a, double b)
		{
			CHECK_LEN();
			if (!checkKeyInvalid(name))
            {
                return;
            }

            auto& keyInfo = m_doc["head"][name];
            if (!checkNumValue(keyInfo[1].GetInt()))
            {
                return;
            }
            auto& comp = m_pCompList[m_nCompListLen];
            comp->initBetween(keyInfo[0].GetInt(), a, b);
            m_nCompListLen++;
		}

		void addIn(const char* name, const double* number, int count)
		{
			if (count <= 0)
			{
                m_errorCode = QueryError::queryInCountError;
				printf("Error addIn, count: %d!\n", count);
				return;
			}
			CHECK_LEN();
			if (!checkKeyInvalid(name))
            {
                return;
            }

            auto& keyInfo = m_doc["head"][name];
            if (!checkNumValue(keyInfo[1].GetInt()))
            {
                return;
            }
            auto& comp = m_pCompList[m_nCompListLen];
            comp->initIn(keyInfo[0].GetInt(), number, count);
            m_nCompListLen++;
		}

		void addIn(const char* name, const char** str, int count)
		{
			if (count <= 0)
			{
                m_errorCode = QueryError::queryInCountError;
				printf("Error addIn, count: %d!\n", count);
				return;
			}
			CHECK_LEN();
			if (!checkKeyInvalid(name))
            {
                return;
            }

            auto& keyInfo = m_doc["head"][name];
            if (!checkStrValue(keyInfo[1].GetInt()))
            {
                return;
            }
            auto& comp = m_pCompList[m_nCompListLen];
            comp->initIn(keyInfo[0].GetInt(), str, count);
            m_nCompListLen++;
		}

		int query()
		{
			int index = 0;
			int bestIndex = -1;
			int len = MAX_LEN;
			m_vResult.clear();
			m_vecIndexResult.clear();
			while (index < m_nCompListLen)
			{

				auto it = m_pDataMap.find(m_pCompList[index]->m_nIndex);
			 	if (it != m_pDataMap.end())
			 	{
			 		CompBase& comp = *m_pCompList[index];
			 		if (comp.getKeyIndexLen(comp, m_vecIndexResult, it->second, len))
			 		{
			 			bestIndex = index;
			 			if (len == 0 || len == 1)
			 			{
			 				break;
			 			}
			 		}
			 	}
				index++;
			}
			index = bestIndex;
			if (bestIndex != -1)
			{
				auto it = m_pDataMap.find(m_pCompList[index]->m_nIndex);
				if (it != m_pDataMap.end())
				{
					len = MAX_LEN;
					CompBase& comp = *m_pCompList[index];
					comp.getKeyIndex(comp, m_vecIndexResult, it->second, len);
				}
				else
				{
					bestIndex = -1;
				}
			}

			if (bestIndex == -1)
			{
				return simpleQuery();
			}
			m_vResult.reserve(len);
			
			if (index != m_nCompListLen-1)
			{
				CompBase* tmp = m_pCompList[index];
				m_pCompList[index] = m_pCompList[m_nCompListLen-1];
				m_pCompList[m_nCompListLen-1] = tmp;
			}
			switch (m_nCompListLen)
			{
				case 1: return queryLoop(); break;
				case 2: return queryLoop(*m_pCompList[0]); break;
				case 3: return queryLoop(*m_pCompList[0], *m_pCompList[1]); break;
				case 4: return queryLoop(*m_pCompList[0], *m_pCompList[1], *m_pCompList[2]); break;
				case 5: return queryLoop(*m_pCompList[0], *m_pCompList[1], *m_pCompList[2], *m_pCompList[3]); break;
				case 6: return queryLoop(*m_pCompList[0], *m_pCompList[1], *m_pCompList[2], *m_pCompList[3], *m_pCompList[4]); break;
				case 7: return queryLoop(*m_pCompList[0], *m_pCompList[1], *m_pCompList[2], *m_pCompList[3], *m_pCompList[4], *m_pCompList[5]); break;
				case 8: return queryLoop(*m_pCompList[0], *m_pCompList[1], *m_pCompList[2], *m_pCompList[3], *m_pCompList[4], *m_pCompList[5], *m_pCompList[6]); break;
				default:
                    m_errorCode = QueryError::compTooMoreOrLess;
                    printf("Error CompListLen: %d\n", m_nCompListLen); m_nCompListLen = 0; break;
			}
			return 0;
		}

        void orderByResult(const char* key)
        {
			auto& head = m_doc["head"];
			if (!head.HasMember(key))
			{
				m_errorCode = QueryError::orderKeyNotFound;
				return;
			}
            auto& keyInfo = m_doc["head"][key];
            int keyIndex = keyInfo[0].GetInt();
            int keyType = keyInfo[1].GetInt();
            auto& datas = m_doc["datas"];

            SORT_RESULT_BODY1
            if (keyType == DBTYPE_NUM)
            {
                return data1.GetDouble() < data2.GetDouble();
            }
            else
            {
            	return strcmp(data1.GetString(), data2.GetString()) < 0;
            }
            SORT_RESULT_BODY2
        }

		void genLuaResultItem(struct lua_State* L, short index)
		{
			auto& keys = m_doc["keys"];
			auto& datas = m_doc["datas"];
            if (index > datas.Size())
            {
                printf("result index:%d is too large then %d\n", datas.Size(), index);
                m_errorCode = QueryError::resultIndexError;
                return;
            }
			auto& val = datas[index];
			lua_newtable(L);

			int arrLen = val.Size();
			for (int i = 0; i < arrLen; ++i)
			{
				lua_pushstring(L, keys[i].GetString());
				auto& value = val[i];

				if (value.IsNumber())
					lua_pushnumber(L, val[i].GetDouble());
				else if (value.IsNull())
					lua_pushnil(L);
				else
					lua_pushstring(L, value.GetString());

				lua_rawset(L, -3);
			}
		}

		void genLuaResult(struct lua_State* L)
		{
			lua_newtable(L);

			int len = m_vResult.size();
			int index = 0;
			for (int i = 0; i < len; ++i)
			{
				index = m_vResult[i];
				lua_pushinteger(L, i + 1);
				lua_pushinteger(L, index);
				lua_rawset(L, -3);
			}
		}

		vector<unsigned short>& getResult()
        {
            return m_vResult;
        }

        rapidjson::Value& getResultIndex(int index)
        {
            auto& datas = m_doc["datas"];
            return datas[index];
        }

        bool checkError(void)
        {
            return m_errorCode != QueryError::errorNone;
        }

        const char* getErrorMessage(void)
        {
            switch(m_errorCode)
            {
            case errorNone:         return "No error.";
            case jsonParseError:    return "rapidjson parse error.";
            case jsonHeadError:     return "json file without head member.";
            case jsonDatasError:    return "json file without datas member.";
            case jsonKeysError:     return "json file without keys member";
            case indexKeyNotFound:  return "key not found when gen index";
            case compTooMoreOrLess: return "compare condition too more or less";
            case compKeyNotFound:   return "compare key not found";
            case compIsInvalid:     return "compare is not support or invalid";
            case compTypeIsNotNum:  return "query field type isn't 'number'";
            case compTypeIsNotStr:  return "query field type isn't 'string'";
            case queryInCountError: return "query in list count must great then zero";
            case resultIndexError:  return "get result index is invalid";
            case orderKeyNotFound:  return "order key not found";
            default:return "";
            }
        }
    };
}

#endif // !__RE_LEX_H__
