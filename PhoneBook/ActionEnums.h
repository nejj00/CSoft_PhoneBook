#pragma once

/// <summary>
/// Enum за определяне на кой метод извиква UpdateAllViews
/// </summary>
enum ViewAction
{
	ViewActionUpdate,
	ViewActionInsert,
	ViewActionDelete
};

/// <summary>
/// Enum за определяне на кой метод от View класовете отваря диалог
/// </summary>
enum ContextAction
{
	ContextActionUpdate,
	ContextActionInsert,
	ContextActionSelect
};

/// <summary>
/// Enum за определяне на начина по който да се използва сесията в табличния клас
/// </summary>
enum TableSession
{
	InnerSession,
	OuterSession
};