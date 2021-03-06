CXX = g++
CXXFLAGS = -std=c++1y -fPIC
SOFLAGS = -shared -O3
INCLUDE = -I"./"
LIB = -L"./lib/" -L"./DynamicTTree/lib" -L"./CfgManager/lib" -Wl,-rpath=lib/:DynamicTTree/lib/:CfgManager/lib/ -lDTT 

ROOT_LIB := `root-config --libs --glibs`
ROOT_FLAGS := `root-config --cflags --ldflags` -lMathCore -lMathMore

DEPS = DynamicTTree/interface/DynamicTTreeBase.h DynamicTTree/interface/DynamicTTreeInterface.h \
	CfgManager/interface/CfgManager.h CfgManager/interface/CfgManagerT.h \
	interface/WFClass.h interface/WFClassNINO.h interface/WFViewer.h interface/MCPAnalyzer.h \
	interface/RecoTree.h interface/DigiTree.h interface/WFTree.h interface/PositionTree.h interface/H4Tree.h \
	interface/PluginBase.h 
DEPS_OBJS = lib/WFClass.o lib/WFClassNINO.o lib/WFViewer.o lib/MCPAnalyzer.o \
	lib/H4Tree.o lib/RecoTree.o lib/DigiTree.o lib/WFTree.o lib/PositionTree.o lib/PluginBase.o lib/H4Dict.so
PLUG_DEPS = plugins/DigitizerReco.h plugins/MakeCovarianceMatrix.h \
	plugins/HodoReco.h plugins/HodoBTFReco.h plugins/HodoReco.h plugins/WireChamberReco.h \
	plugins/InfoTreeMaker.h plugins/ADCReco.h lib/PluginBase.o
PLUG_OBJS = lib/libDigitizerReco.so lib/libMakeCovarianceMatrix.so \
	lib/libHodoReco.so lib/libHodoBTFReco.so lib/libWireChamberReco.so \
	lib/libInfoTreeMaker.so lib/libADCReco.so
DICT_OBJS = lib/WFViewer.o lib/MCPAnalyzer.o

MAIN = bin/H4Reco

all: dynamicTree cfgManager $(DEPS_OBJS) $(PLUG_OBJS) $(MAIN) lib/LinkDef.cxx 

lib/%.o: src/%.cc $(DEPS)
	$(CXX) $(CXXFLAGS) -c -o $@ $< $(INCLUDE) $(ROOT_LIB) $(ROOT_FLAGS)

lib/lib%.so: plugins/%.cc $(PLUG_DEPS)
	$(CXX) $(CXXFLAGS) $(SOFLAGS) -o $@ $< $(INCLUDE) $(ROOT_LIB) $(ROOT_FLAGS) $(LIB)

lib/LinkDef.cxx: interface/WFViewer.h interface/MCPAnalyzer.h interface/LinkDef.h 
	rootcling -f $@ -c $^

lib/H4Dict.so: lib/LinkDef.cxx $(DICT_OBJS)
	$(CXX) $(CXXFLAGS) $(SOFLAGS) -o $@ $^ $(INCLUDE) $(ROOT_LIB) $(ROOT_FLAGS) $(LIB)

bin/%: main/%.cpp $(DEPS_OBJS) interface/PluginLoader.h CfgManager/lib/CfgManagerDict.so
	$(CXX) $(CXXFLAGS) -ldl -o $@ $^ $(INCLUDE) $(ROOT_LIB) $(ROOT_FLAGS) $(LIB)

CfgManager/lib/CfgManagerDict.so: cfgManager

dynamicTree:
	cd DynamicTTree && $(MAKE)

cfgManager:
	cd CfgManager && $(MAKE)

clean:
	rm -fr tmp/*
	rm -fr lib/*
	rm -fr bin/*
	cd DynamicTTree && $(MAKE) clean
	cd CfgManager && $(MAKE) clean
