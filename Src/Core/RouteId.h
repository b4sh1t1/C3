#pragma once

#include "Common/FSecure/CppTools/ByteConverter/ByteConverter.h"
#include "Identifiers.h"

namespace FSecure::C3
{
	/// A class representing internal C3 connections. Consists of an ID automatically generated by Agents to identify themselves, and an ID of a Channel that was used to establish the connection.
	struct RouteId
	{
		static constexpr size_t BinarySize = AgentId::BinarySize + DeviceId::BinarySize;								///< Length of the Identifier in bytes.

		/// Default ctor.
		constexpr RouteId() = default;

		/// A copy-like public ctor.
		/// @param aid Agent ID.
		/// @param iid Channel ID.
		constexpr RouteId(AgentId aid, DeviceId iid)
			: m_AgentId(std::move(aid))
			, m_InterfaceId(std::move(iid))
		{
		}

		/// Creates a RouteId object from a hex string.
		/// @param textId text containing the identifier.
		RouteId(std::string_view textId);

		/// Creates a RouteId object with a random ("unique") value.
		/// @return Identifier object.
		static RouteId GenerateRandom();

		/// Converts this ID to a string.
		/// @return a string that describes this ID object.
		std::string ToString() const;

		/// Logical negation operator. Can be used to check if ID is set.
		/// @return true if ID is not set.
		bool operator !() const;

		/// Comparison operator.
		/// @param c ID object to compare this to.
		/// @return true if provided ID is the same as this.
		bool operator ==(RouteId const& c) const;

		/// Difference operator.
		/// @param c ID object to compare this to.
		/// @return true if provided ID is different from this.
		bool operator !=(RouteId const& c) const;

		/// The less-than comparison operator.
		/// @param c ID object to compare this to.
		/// @return false if provided ID precedes this.
		bool operator <(RouteId const& c) const;

		/// Checks if ID is set.
		/// @return true if ID is set.
		bool IsNull() const;

		/// AgentId part getter.
		/// @return AgentId part of this RouteId.
		AgentId GetAgentId() const { return m_AgentId; }

		/// InterfaceId part getter.
		/// @return InterfaceId part of this RouteId.
		DeviceId GetInterfaceId() const { return m_InterfaceId; }

		static constexpr size_t TextSize = BinarySize * 2 + 1;															///< Length of the Identifier written in text format (two hex numbers + "." or ":" between them).
		static const RouteId Null;																						///< Object that represents invalid Identifier. Might be used to address special cases (such as Gateway which is a special Relay).

	protected:
		AgentId m_AgentId;																								///< AID part of the connection.
		DeviceId m_InterfaceId;																						///< IID part of the connection.
	};
}

namespace FSecure
{
	/// Specialize ByteConverter for RouteId.
	template <>
	struct ByteConverter<C3::RouteId> : TupleConverter<C3::RouteId>
	{
		static auto TupleTransform(C3::RouteId const& obj)
		{
			return Utils::MakeConversionTuple(obj.GetAgentId(), obj.GetInterfaceId());
		}
	};

}
