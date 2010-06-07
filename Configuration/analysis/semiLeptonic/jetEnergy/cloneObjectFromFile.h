template <typename T>
T cloneObjectFromFile(TFile* file, TString name)
{
  if(!file->Get(name)) {
    std::cout << "Failed to get object with name " << name << " from file " << file->GetName() << std::endl;
    abort();
  }
  T obj = (T) file->Get(name);
  for(unsigned i=0; i<999999; i++) {
    TString cloneName = (TString) obj->GetName() + "_clone_";
    cloneName += i;
    if(!gDirectory->Get(cloneName)) {
      return (T) file->Get(name)->Clone(cloneName);
    }
  }
  std::cout << "Already more than 999999 clones from object with name " << obj->GetName() << std::endl
	    << "If this is really what you want, you have to increase this hard-coded limit in the macro." << std::endl;
  abort();
}
