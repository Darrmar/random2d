namespace random2d {

	class road{

		public:

			unsigned int nextNumber;
			float fV;
			int pnum = 0;
			int massF[10];
			unsigned int arrMNumber;
			int checkM(unsigned int cm);
			int checkA(unsigned int caa, unsigned int cmm);
			int checkC(unsigned int acc, unsigned int amm);
			int checkX(unsigned int cxx, unsigned int cxm);
			unsigned int formulaCheck(unsigned int fm, unsigned int fx, unsigned int fa, unsigned int fc, unsigned int fnCount);
	};

}

