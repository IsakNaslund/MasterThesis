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
			_util[name].Clear();
		else
			_util.insert(std::pair<std::string, UtilisationSet>(name, UtilisationSet()));

		if (!(std::find(_loadCases.begin(), _loadCases.end(), name) != _loadCases.end()))
		{
			_loadCases.push_back(name);
		}

	}

	void ElementResults3d::ClearLoadComb(std::string name)
	{
		// Remove loadcase if found
		if (_N.find(name) != _N.end())
			_N.erase(name);

		// Remove loadcase if found
		if (_Vy.find(name) != _Vy.end())
			_Vy.erase(name);

		// Remove loadcase if found
		if (_Vz.find(name) != _Vz.end())
			_Vz.erase(name);

		// Remove loadcase if found
		if (_T.find(name) != _T.end())
			_T.erase(name);

		// Remove loadcase if found
		if (_Mz.find(name) != _Mz.end())
			_Mz.erase(name);

		// Remove loadcase if found
		if (_My.find(name) != _My.end())
			_My.erase(name);


		// Remove loadcase if found
		if (_u.find(name) != _u.end())
			_u.erase(name);

		// Remove loadcase if found
		if (_v.find(name) != _v.end())
			_v.erase(name);

		// Remove loadcase if found
		if (_w.find(name) != _w.end())
			_w.erase(name);

		// Remove loadcase if found
		if (_fi.find(name) != _fi.end())
			_fi.erase(name);


		// Remove loadcase if found
		if (_util.find(name) != _util.end())
			_util.erase(name);

		std::vector<std::string>::iterator iter = std::find(_loadCases.begin(), _loadCases.end(), name);

		if (iter != _loadCases.end())
		{
			_loadCases.erase(iter);
		}
	}

	void ElementResults3d::CalcMaxUtil()
	{
		_maxUtil.Reset();

		for each (std::pair<std::string, UtilisationSet> utilPair in _util)
		{
			_maxUtil.Update(utilPair.second.MaxUtil().GetUtil(), utilPair.first + " " + utilPair.second.MaxUtil().GetDesc());
		}
	}

	void ElementResults3d::ScaleForcesAndDeformations(std::string loadComb, double sFac)
	{
		for (int i = 0; i < _N[loadComb].size(); i++)
		{
			_N[loadComb][i] *= sFac;
		}

		for (int i = 0; i < _Vy[loadComb].size(); i++)
		{
			_Vy[loadComb][i] *= sFac;
		}

		for (int i = 0; i < _Vz[loadComb].size(); i++)
		{
			_Vz[loadComb][i] *= sFac;
		}

		for (int i = 0; i < _T[loadComb].size(); i++)
		{
			_T[loadComb][i] *= sFac;
		}

		for (int i = 0; i <  _My[loadComb].size(); i++)
		{
			_My[loadComb][i] *= sFac;
		}

		for (int i = 0; i < _Mz[loadComb].size(); i++)
		{
			_Mz[loadComb][i] *= sFac;
		}

		for (int i = 0; i < _v[loadComb].size(); i++)
		{
			_v[loadComb][i] *= sFac;
		}

		for (int i = 0; i < _u[loadComb].size(); i++)
		{
			_u[loadComb][i] *= sFac;
		}

		for (int i = 0; i < _w[loadComb].size(); i++)
		{
			_w[loadComb][i] *= sFac;
		}

		for (int i = 0; i < _fi[loadComb].size(); i++)
		{
			_fi[loadComb][i] *= sFac;
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

		_loadCases.clear();
	}

	void ElementResults3d::MaxMomentSection(double & my, double & mz)
	{
		double max = -1e99;

		for (int i = 0; i < _loadCases.size(); i++)
		{
			for (int j = 0; j < _My[_loadCases[i]].size(); j++)
			{
				double totSquared = pow(_My[_loadCases[i]][j], 2) + pow(_Mz[_loadCases[i]][j], 2);
				if (totSquared > max)
				{
					max = totSquared;
					my = _My[_loadCases[i]][j];
					mz = _Mz[_loadCases[i]][j];
				}
					
			}
		}

	}
}