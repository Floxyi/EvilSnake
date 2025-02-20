CACHE_DIR = .cache
ASSETS_DIR = assets
SOURCES = $(wildcard src/*.cpp include/*.h)

BUILD_DIR = build
GAME = $(BUILD_DIR)/EvilSnake

MACOS_BUILD_DIR = build_macos
MACOS_GAME = $(MACOS_BUILD_DIR)/EvilSnake
APP_BUNDLE = $(MACOS_GAME).app
INFO_PLIST = platform/macos/Info.plist
ENTITLEMENTS_PLIST = platform/macos/entitlements.plist
APP_ICON = platform/macos/AppIcon.icns

$(BUILD_DIR) $(MACOS_BUILD_DIR):
	mkdir -p $@

$(GAME): $(SOURCES) $(BUILD_DIR)
	cd $(BUILD_DIR) && cmake .. && cmake --build .

$(MACOS_GAME): $(SOURCES) $(MACOS_BUILD_DIR)
	cd $(MACOS_BUILD_DIR) && cmake .. -DMACOS_BUILD=ON && cmake --build .

run: $(GAME)
	./$(GAME)

build-macos: $(MACOS_GAME)
	@mkdir -p $(APP_BUNDLE)/Contents/MacOS $(APP_BUNDLE)/Contents/Resources
	cp $(MACOS_GAME) $(APP_BUNDLE)/Contents/MacOS/
	cp $(INFO_PLIST) $(APP_BUNDLE)/Contents/
	cp $(APP_ICON) $(APP_BUNDLE)/Contents/Resources/
	cp -R $(ASSETS_DIR) $(APP_BUNDLE)/Contents/Resources/
	codesign --deep --force --verbose --entitlements $(ENTITLEMENTS_PLIST) --sign - $(APP_BUNDLE)
	open $(APP_BUNDLE)

dev: $(BUILD_DIR)
	cd $(BUILD_DIR) && cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON ..

clean:
	rm -rf $(BUILD_DIR) $(MACOS_BUILD_DIR) $(CACHE_DIR)
	make dev
