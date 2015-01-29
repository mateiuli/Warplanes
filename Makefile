CC=g++
CFLAGS=-Wall -std=c++11 
LDFLAGS=-lsfml-graphics -lsfml-window -lsfml-system
EXE=TheGame
OBJECTS= DataTables.o Button.o Label.o Container.o Component.o ParallelTask.o SettingsState.o FadeOutState.o FadeInState.o LoadingState.o PauseState.o MenuState.o TitleState.o GameState.o Application.o State.o StateStack.o Command.o CommandQueue.o Player.o Projectile.o Entity.o Aircraft.o TextNode.o SpriteNode.o SceneNode.o World.o Utility.o main.o

all: $(OBJECTS)
	$(CC) $(OBJECTS) -o $(EXE) $(LDFLAGS)

%.o: %.cpp
	$(CC) -c $< -o $@ $(CFLAGS)

clean:
	rm -f *.o $(EXE)

.PHONY: build clean
