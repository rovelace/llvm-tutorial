#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/IRBuilder.h"

#include "InsertIncFunction.h"

bool InsertIncFunction::runOnModule(Module &M) {

	Type * intTy = Type::getInt32Ty(M.getContext());
	Constant *One = ConstantInt::get( intTy, 1);
	FunctionCallee fc = M.getOrInsertFunction("inc", intTy, intTy);
	Function * callee = dyn_cast<Function>(fc.getCallee());
	BasicBlock *entry = BasicBlock::Create(M.getContext(), "entry", callee);
	IRBuilder<> Builder(entry);
	//Argument * Arg = callee->args().begin();
	Argument * Arg = callee->getArg(0);
	Value * Add= Builder.CreateAdd(Arg, One);	
	Builder.CreateRet(Add);
    return true;
}


void InsertIncFunction::getAnalysisUsage(AnalysisUsage &AU) const {
    AU.setPreservesAll();
}

char InsertIncFunction::ID = 0;
static RegisterPass<InsertIncFunction> X("insert-inc-fun", "Hello World Pass ");
