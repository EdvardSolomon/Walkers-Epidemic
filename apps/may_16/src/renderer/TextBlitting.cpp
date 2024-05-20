#include "TextBlitter.h"
#include <unordered_map>

namespace TextBlitter {

    int _xMargin = 0;
    int _yMargin = 0;
    int _xDebugMargin = 0;
    int _yDebugMargin = 4;
    int _charSpacing = 0;
    int _spaceWidth = 6;
    std::string _charSheet = "�!\"#$%&\'��*+,-./0123456789:;<=>?_ABCDEFGHIJKLMNOPQRSTUVWXYZ\\^_`abcdefghijklmnopqrstuvwxyz";
    std::string _numSheet = "0123456789/";
    int _charCursorIndex = 0;
    float _textTime = 0;
    float _textSpeed = 200.0f;
    float _countdownTimer = 0;
    float _delayTimer = 0;

    // Заглушки для размеров текстур и индексов
    std::unordered_map<std::string, ivec2> textureSizes;
    std::unordered_map<std::string, int> textureIndices;

    // Функция для инициализации заглушек
    void InitializeStubTextures() {
        // Предположим, что все символы имеют размер 16x16 пикселей
        for (size_t i = 0; i < _charSheet.size(); ++i) {
            std::string textureName = "char_" + std::to_string(i + 1);
            textureSizes[textureName] = ivec2(16, 16);
            textureIndices[textureName] = static_cast<int>(i);
        }
        for (size_t i = 0; i < _numSheet.size(); ++i) {
            std::string textureName = "num_" + std::to_string(i);
            textureSizes[textureName] = ivec2(16, 16);
            textureIndices[textureName] = static_cast<int>(i);
        }
    }
}

int TextBlitter::GetLineHeight(BitmapFontType fontType) {
    if (fontType == BitmapFontType::STANDARD) {
        return 16;
    }
    else if (fontType == BitmapFontType::AMMO_NUMBERS) {
        return 34;
    }
    else {
        return 0;
    }
}

ivec2 TextBlitter::GetCharacterSize(const char* character, BitmapFontType fontType) {
    if (fontType == BitmapFontType::STANDARD) {
        int charPos = _charSheet.find(character);
        std::string textureName = "char_" + std::to_string(charPos + 1);
        return textureSizes[textureName];
    }
    else if (fontType == BitmapFontType::AMMO_NUMBERS) {
        int charPos = _numSheet.find(character);
        std::string textureName = "num_" + std::to_string(charPos);
        return textureSizes[textureName];
    }
    else {
        return ivec2(0, 0);
    }
}

std::vector<RenderItem2D> TextBlitter::CreateText(std::string text, ivec2 location, ivec2 viewportSize, Alignment alignment, BitmapFontType fontType, glm::vec2 scale) {

    std::vector<RenderItem2D> renderItems;

    if (alignment == Alignment::TOP_LEFT || alignment == Alignment::TOP_RIGHT) {
        location.y -= GetLineHeight(fontType) * scale.y;
    }
    if (alignment == Alignment::TOP_RIGHT || alignment == Alignment::BOTTOM_RIGHT) {
        location.x -= GetTextSizeInPixels(text, viewportSize, fontType, scale).x;
    }

    glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f); // Белый цвет
    int xcursor = location.x;
    int ycursor = location.y;

    for (int i = 0; i < text.length(); i++) {
        char character = text[i];
        if (text[i] == '[' &&
            text[(size_t)i + 1] == 'w' &&
            text[(size_t)i + 2] == ']') {
            i += 2;
            color = glm::vec3(1.0f, 1.0f, 1.0f); // Белый цвет
            continue;
        }
        else if (text[i] == '[' &&
            text[(size_t)i + 1] == 'g' &&
            text[(size_t)i + 2] == ']') {
            i += 2;
            color = glm::vec3(0.0f, 1.0f, 0.0f); // Зеленый цвет
            continue;
        }
        else if (text[i] == '[' &&
            text[(size_t)i + 1] == 'r' &&
            text[(size_t)i + 2] == ']') {
            i += 2;
            color = glm::vec3(1.0f, 0.0f, 0.0f); // Красный цвет
            continue;
        }
        else if (text[i] == '[' &&
            text[(size_t)i + 1] == 'l' &&
            text[(size_t)i + 2] == 'g' &&
            text[(size_t)i + 3] == ']') {
            i += 3;
            color = glm::vec3(0.5f, 1.0f, 0.5f); // Светло-зеленый цвет
            continue;
        }
        else if (text[i] == '[' &&
            text[(size_t)i + 1] == 'l' &&
            text[(size_t)i + 2] == 'r' &&
            text[(size_t)i + 3] == ']') {
            i += 3;
            color = glm::vec3(1.0f, 0.5f, 0.5f); // Светло-красный цвет
            continue;
        }
        else if (character == ' ') {
            xcursor += _spaceWidth;
            continue;
        }
        else if (character == '\n') {
            xcursor = location.x;
            ycursor -= GetLineHeight(fontType) * scale.y;
            continue;
        }

        std::string textureName = "";
        size_t charPos = std::string::npos;

        if (fontType == BitmapFontType::STANDARD) {
            charPos = _charSheet.find(character);
            textureName = "char_" + std::to_string(charPos + 1);
        }
        if (fontType == BitmapFontType::AMMO_NUMBERS) {
            charPos = _numSheet.find(character);
            textureName = "num_" + std::to_string(charPos);
        }

        if (charPos == std::string::npos) {
            continue;
        }

        // Get texture index and dimensions
        int textureIndex = textureIndices[textureName];
        ivec2 textureSize = textureSizes[textureName];
        float texWidth = textureSize.x * scale.x;
        float texHeight = textureSize.y * scale.y;
        float width = (1.0f / viewportSize.x) * texWidth;
        float height = (1.0f / viewportSize.y) * texHeight;
        float cursor_X = ((xcursor + (texWidth / 2.0f)) / viewportSize.x) * 2 - 1;
        float cursor_Y = ((ycursor + (texHeight / 2.0f)) / viewportSize.y) * 2 - 1;

        Transform transform;
        transform.position.x = cursor_X;
        transform.position.y = cursor_Y;
        transform.scale = glm::vec3(width, height * -1, 1);

        RenderItem2D renderItem;
        renderItem.modelMatrix = transform.to_mat4();
        renderItem.textureIndex = textureIndex;
        renderItem.colorTintR = color.r;
        renderItem.colorTintG = color.g;
        renderItem.colorTintB = color.b;
        renderItems.push_back(renderItem);

        xcursor += texWidth + _charSpacing;
    }
    return renderItems;
}

ivec2 TextBlitter::GetTextSizeInPixels(std::string text, ivec2 viewportSize, BitmapFontType fontType, glm::vec2 scale) {

    int xcursor = 0;
    int ycursor = 0;
    int maxWidth = 0;
    int maxHeight = 0;

    for (int i = 0; i < text.length(); i++) {
        char character = text[i];
        if (text[i] == '[' &&
            text[(size_t)i + 2] == ']') {
            i += 2;
            continue;
        }
        else if (text[i] == '[' &&
            text[(size_t)i + 1] == 'l' &&
            text[(size_t)i + 3] == ']') {
            i += 3;
            continue;
        }
        else if (character == ' ') {
            xcursor += _spaceWidth;
            continue;
        }
        else if (character == '\n') {
            xcursor = 0;
            ycursor -= GetLineHeight(fontType) * scale.y;
            continue;
        }

        std::string textureName = "";
        size_t charPos = std::string::npos;

        if (fontType == BitmapFontType::STANDARD) {
            charPos = _charSheet.find(character);
            textureName = "char_" + std::to_string(charPos + 1);
        }
        if (fontType == BitmapFontType::AMMO_NUMBERS) {
            charPos = _numSheet.find(character);
            textureName = "num_" + std::to_string(charPos);
        }

        if (charPos == std::string::npos) {
            continue;
        }

        // Get texture index and dimensions
        ivec2 textureSize = textureSizes[textureName];
        float texWidth = textureSize.x * scale.x;
        float texHeight = textureSize.y * scale.y;
        xcursor += texWidth + _charSpacing;
        maxWidth = std::max(maxWidth, xcursor);
        maxHeight = std::max(maxWidth, ycursor);
    }

    return ivec2(maxWidth, maxHeight);
}
