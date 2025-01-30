BUILD_DIR = build
GAME = $(BUILD_DIR)/game

all: $(BUILD_DIR) $(GAME)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

SOURCES = $(wildcard src/*.cpp)

$(GAME): $(SOURCES)
	cd $(BUILD_DIR) && cmake .. && cmake --build .


run: all
	./$(GAME)

clean:
	rm -rf $(BUILD_DIR)
