CACHE_DIR = .cache
BUILD_DIR = build
APP_DIR = build_macos
APP_BUNDLE = $(APP_DIR)/EvilSnake.app

GAME = $(BUILD_DIR)/EvilSnake

INFO_PLIST = platform/macos/Info.plist
APP_ICON = platform/macos/AppIcon.icns
ASSETS_DIR = assets

all: $(BUILD_DIR) $(GAME)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

SOURCES = $(wildcard src/*.cpp include/*.h)

$(GAME): $(SOURCES)
	cd $(BUILD_DIR) && cmake .. && cmake --build .

run: clean all
	./$(GAME)

build-macos: clean $(BUILD_DIR)
	mkdir -p $(APP_DIR)
	mkdir -p $(APP_BUNDLE)/Contents/MacOS
	mkdir -p $(APP_BUNDLE)/Contents/Resources
	cd $(BUILD_DIR) && cmake .. -DMACOS_BUILD=ON && cmake --build .
	cp $(GAME) $(APP_BUNDLE)/Contents/MacOS/
	cp $(INFO_PLIST) $(APP_BUNDLE)/Contents/
	cp $(APP_ICON) $(APP_BUNDLE)/Contents/Resources/
	cp -R $(ASSETS_DIR) $(APP_BUNDLE)/Contents/Resources/
	codesign --deep --force --verbose --sign - $(APP_BUNDLE)

clean:
	rm -rf $(BUILD_DIR) $(APP_DIR) $(CACHE_DIR)
