#pragma once
#include "pch.h"

class LabelEditor
{
public:
	LabelEditor() = default;

	struct label
	{
		const char* label_;
		const char* text;
		label(const char* l, const char* t)
			: label_(l), text(t)
		{ }
	};

	inline void setLabel(const char* label_, const char* text) {
		g_labels.push_back(label(label_, text));
	}

	inline std::vector<label> get_vector() {
		return g_labels;
	}

private:
	std::vector<label> g_labels{};
};

inline std::unique_ptr<LabelEditor> g_label;