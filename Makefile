########################################
## SETUP MAKEFILE
##      Set the appropriate TARGET (our
## executable name) and any OBJECT files
## we need to compile for this program.
##
## Next set the path to our local
## include/, lib/, and bin/ folders.
## (If you we are compiling in the lab,
## then you can ignore these values.
## They are only for if you are
## compiling on your personal machine.)
##
## Set if we are compiling in the lab
## environment or not.  Set to:
##    1 - if compiling in the Lab
##    0 - if compiling at home
##
## Finally, set the flags for which
## libraries you are using and want to
## compile against.
########################################

TARGET = GuildWars

SOURCES = $(shell find src -name '*.cpp')
OBJECTS = $(SOURCES:src/%.cpp=bin/%.o)
DEPS = $(SOURCES:src/%.cpp=bin/%.d)

LOCAL_INC_PATH = /opt/local/include
LOCAL_LIB_PATH = /opt/local/lib
LOCAL_BIN_PATH = /opt/local/bin

BUILDING_IN_LAB = 1

USING_OPENGL = 1
USING_OPENAL = 1

#########################################################################################
#########################################################################################
#########################################################################################
##
## !!!STOP!!!
## THERE IS NO NEED TO MODIFY ANYTHING BELOW THIS LINE
## IT WILL WORK FOR YOU.  TRUST ME





#############################
## COMPILING INFO
#############################

CXX    = g++
CFLAGS = -Wall -g

INCPATH += -I./include

LAB_INC_PATH = C:/sw/opengl/include
LAB_LIB_PATH = C:/sw/opengl/lib
LAB_BIN_PATH = C:/sw/opengl/bin

# if we are not building in the Lab
ifeq ($(BUILDING_IN_LAB), 0)
    # and we are running Windows
    ifeq ($(OS), Windows_NT)
        # then set our lab paths to our local paths
        # so the Makefile will still work seamlessly
        LAB_INC_PATH = $(LOCAL_INC_PATH)
        LAB_LIB_PATH = $(LOCAL_LIB_PATH)
        LAB_BIN_PATH = $(LOCAL_BIN_PATH)
    endif
endif

#############################
## SETUP OpenGL & GLUT 
#############################

# if we are using OpenGL & GLUT in this program
ifeq ($(USING_OPENGL), 1)
    # Windows builds
    ifeq ($(OS), Windows_NT)
        INCPATH += -I$(LAB_INC_PATH)
        LIBPATH += -L$(LAB_LIB_PATH)
        LIBS += -lglut -lopengl32 -lglu32

    # Mac builds
    else ifeq ($(shell uname), Darwin)
	LIBS += -framework GLUT -framework OpenGL

    # Linux and all other builds
    else
        LIBS += -lglut -lGL -lGLU
    endif
endif

#############################
## SETUP OpenAL & ALUT
#############################

# if we are using OpenAL & GLUT in this program
ifeq ($(USING_OPENAL), 1)
    # Windows builds
    ifeq ($(OS), Windows_NT)
        INCPATH += -I$(LAB_INC_PATH)
        LIBPATH += -L$(LAB_LIB_PATH)
        LIBS += -lalut.dll -lOpenAL32.dll

    # Mac builds
    else ifeq ($(shell uname), Darwin)
        INCPATH += -I$(LOCAL_INC_PATH)
        LIBPATH += -L$(LOCAL_LIB_PATH)
        LIBS += -framework OpenAL

    # Linux and all other builds
    else
        INCPATH += -I$(LOCAL_INC_PATH)
        LIBPATH += -L$(LOCAL_LIB_PATH)
        LIBS += -lalut -lopenal
    endif
endif


#############################
## COMPILATION INSTRUCTIONS 
#############################

all: $(TARGET)

test: all
	./$(TARGET) test.csv

clean:
	rm -f $(OBJECTS) $(TARGET)

rebuild: clean all
		./$(TARGET)

#depend:
#	rm -f Makefile.bak
#	mv Makefile Makefile.bak
#	sed '/^# DEPENDENCIES/,$$d' Makefile.bak > Makefile
#	echo '# DEPENDENCIES' >> Makefile
#	$(CXX) $(INCPATH) -MM *.cpp >> Makefile

#.c.o: 	
#	$(CXX) $(CFLAGS) $(INCPATH) -c -o $@ $<

#.cc.o: 	
#	$(CXX) $(CFLAGS) $(INCPATH) -c -o $@ $<

#.cpp.o: 	
#	$(CXX) $(CFLAGS) $(INCPATH) -c -o $@ $<

$(TARGET): $(OBJECTS) 
	$(CXX) $(CFLAGS) $(INCPATH) -o $@ $^ $(LIBPATH) $(LIBS)

	#$(CXX) $(COMMONFLAGS) $^ -o $(NAME)
#ensures the bin directory is created
$(SOURCES): | bin


bin:
		mkdir -p $(shell find src -type d | sed "s/src/bin/")

bin/%.o: src/%.cpp
	$(CXX) $(CFLAGS) $(INCPATH) $^ -c -o $@ $(LIBPATH) $(LIBS)

 # if we are using OpenAL, then we need to copy the runtime
    # files to our executable directory...and only if we are on
    # Windows.  The other OSes should be set up globally.
    ifeq ($(USING_OPENAL), 1 )
        # Windows builds
        ifeq ($(OS), Windows_NT)
            cp $(LAB_BIN_PATH)/OpenAL32.dll .
            cp $(LAB_BIN_PATH)/libalut.dll .
        endif
    endif



# DEPENDENCIES
#Auto dependency management.
-include $(DEPS)
