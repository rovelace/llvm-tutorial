#include "llvm/Support/raw_ostream.h"
#include "llvm/Support/Debug.h"

#include "FunctionNamePrinter.h"


bool FunctionNamePrinter::runOnFunction(Function &F) {
	dbgs() << F.getName() <<"\n";
    return false;
}

void FunctionNamePrinter::getAnalysisUsage(AnalysisUsage &AU) const {
    AU.setPreservesAll();
}

char FunctionNamePrinter::ID = 0;
static RegisterPass<FunctionNamePrinter> Y("fun-name-printer", "Hello World Pass ");
