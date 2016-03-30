#include "ElementResults3d.h"

namespace CIFem
{
	void ElementResults3d::SetUpLoadComb(std::string name)
	{
		// Find or create result object
		if (_N.find(name) != _N.end())
			_N[name].clear();
		else
			_N.insert(std::pair<std::string,std::vector<double>>(name, std::vector<double>()));

		// Find or create result object
		if (_Vy.find(name) != _Vy.end())
			_Vy[name].clear();
		else
			_Vy.insert(std::pair<std::string, std::vector<double>>(name, std::vector<double>()));

		// Find or create result object
		if (_Vz.find(name) != _Vz.end())
			_Vz[name].clear();
		else
			_Vz.insert(std::pair<std::string, std::vector<double>>(name, std::vector<double>()));

		// Find or create result object
		if (_T.find(name) != _T.end())
			_T[name].clear();
		else
			_T.insert(std::pair<std::string, std::vector<double>>(name, std::vector<double>()));

		// Find or create result object
		if (_Mz.find(name) != _Mz.end())
			_Mz[name].clear();
		else
			_Mz.insert(std::pair<std::string, std::vector<double>>(name, std::vector<double>()));

		// Find or create result object
		if (_My.find(name) != _My.end())
			_My[name].clear();
		else
			_My.insert(std::pair<std::string, std::vector<double>>(name, std::vector<double>()));


		// Find or create result object
		if (_u.find(name) != _u.end())
			_u[name].clear();
		else
			_u.insert(std::pair<std::string, std::vector<double>>(name, std::vector<double>()));

		// Find or create result object
		if (_v.find(name) != _v.end())
			_v[name].clear();
		else
			_v.insert(std::pair<std::string, std::vector<double>>(name, std::vector<double>()));

		// Find or create result object
		if (_w.find(name) != _w.end())
			_w[name].clear();
		else
			_w.insert(std::pair<std::string, std::vector<double>>(name, std::vector<double>()));

		// Find or create result object
		if (_fi.find(name) != _fi.end())
			_fi[name].clear();
		else
			_fi.insert(std::pair<std::string, std::vector<double>>(name, std::vector<double>()));


		// Find or create result object
		if (_util.find(name) != _util.end())
			_util[name].clear();
		else
			_util.insert(std::pair<std::string, std::vector<std::shared_ptr<Utilisation>>>(name, std::vector<std::shared_ptr<Utilisation>>()));

	}

	void ElementResults3d::CalcMaxUtil()
	{
		for each (std::pair<std::string, std::vector<std::shared_ptr<Utilisation>>> utilPair in _util)
		{
			for (int i = 0; i < utilPair.second.size(); i++)
			{
				_maxUtil.Update(utilPair.second[i]->GetUtil(), utilPair.first + " " + utilPair.second[i]->GetDesc());
			}
		}
	}

	ElementResults3d::ElementResults3d()
	{
	}


	ElementResults3d::~ElementResults3d()
	{
	}


	void ElementResults3d::Reset()
	{
		_N.clear();
		_Vy.clear();
		_Vz.clear();
		_T.clear();
		_My.clear();
		_Mz.clear();
		_u.clear();
		_v.clear();
		_w.clear();
		_fi.clear();
		_pos.clear();

		_util.clear();
		_maxUtil.Reset();
	}
}