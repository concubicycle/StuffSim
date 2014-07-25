#include "path_tests.h"

using StuffSim::Path;

using std::endl;
using StuffSim::cout;


void run_path_tests()
{
	std::cout << "######## PATH TEST ############" << std::endl;

	cout << SSIM_STR_LIT("Executable: ") << Path::getExecutablePath().getFullPathStr() << endl;

	Path textbooksPath(L"D:\\Textbooks\\..\\.\\Textbooks\\ML-Related");
	cout << SSIM_STR_LIT("Raw: ") << textbooksPath.getFullPathStr() << endl;

	textbooksPath.normalize();
	cout << SSIM_STR_LIT("Normalized: ") << textbooksPath.getFullPathStr() << endl;

	cout << SSIM_STR_LIT("Is a valid path: ") << textbooksPath.isValid() << endl;

	cout << SSIM_STR_LIT("pathDirStr: ") << textbooksPath.pathDirStr() << endl;
	cout << SSIM_STR_LIT("pathDir: ") << textbooksPath.pathDir().getFullPathStr() << endl;

	cout << endl << endl;

	OSString aStr = SSIM_STR_LIT("D:\\Development\\Bullet\\");
	OSString bStr = SSIM_STR_LIT("bullet3\\bin");

	addPaths(aStr, bStr);

	aStr = SSIM_STR_LIT("D:\\Development\\Bullet");

	addPaths(aStr, bStr);

	bStr = SSIM_STR_LIT(".\\bullet3\\bin");

	addPaths(aStr, bStr);

	aStr = SSIM_STR_LIT("D:\\Development\\Bullet\\");

	addPaths(aStr, bStr);



	Path withDot(aStr + bStr);
	withDot.normalize();

	cout << SSIM_STR_LIT("Normalized: ") << withDot.getFullPathStr() << endl;

	Path relative(SSIM_STR_LIT("..\\..\\Debug"));

	cout << endl;

	cout << SSIM_STR_LIT("relative: ") << relative.getFullPathStr() << endl;
	relative.makeFullyResolved();
	cout << SSIM_STR_LIT("fully resolved relative: ") << relative.getFullPathStr() << endl;
	relative.normalize();
	cout << SSIM_STR_LIT("normalized relative: ") << relative.getFullPathStr() << endl;	


	Path d = relative;
	cout << SSIM_STR_LIT("copy relative: ") << d.getFullPathStr() << endl;
}

void addPaths(OSString& one, OSString& two)
{
	Path a(one);
	Path b(two);

	cout << one << SSIM_STR_LIT(" + ") << two << SSIM_STR_LIT(": ") << endl << (a + b).getFullPathStr() << endl;
	cout << SSIM_STR_LIT("Is valid: ") << (a + b).isValid() << endl << endl;
}

