// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: ClientData.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_ClientData_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_ClientData_2eproto

#include <limits>
#include <string>

#include <google/protobuf/port_def.inc>
#if PROTOBUF_VERSION < 3009000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers. Please update
#error your headers.
#endif
#if 3009000 < PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers. Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/port_undef.inc>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_table_driven.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/inlined_string_field.h>
#include <google/protobuf/metadata.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
#define PROTOBUF_INTERNAL_EXPORT_ClientData_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_ClientData_2eproto {
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTableField entries[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::AuxillaryParseTableField aux[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTable schema[1]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::FieldMetadata field_metadata[];
  static const ::PROTOBUF_NAMESPACE_ID::internal::SerializationTable serialization_table[];
  static const ::PROTOBUF_NAMESPACE_ID::uint32 offsets[];
};
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_ClientData_2eproto;
namespace Data {
class ClientData;
class ClientDataDefaultTypeInternal;
extern ClientDataDefaultTypeInternal _ClientData_default_instance_;
}  // namespace Data
PROTOBUF_NAMESPACE_OPEN
template<> ::Data::ClientData* Arena::CreateMaybeMessage<::Data::ClientData>(Arena*);
PROTOBUF_NAMESPACE_CLOSE
namespace Data {

// ===================================================================

class ClientData :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:Data.ClientData) */ {
 public:
  ClientData();
  virtual ~ClientData();

  ClientData(const ClientData& from);
  ClientData(ClientData&& from) noexcept
    : ClientData() {
    *this = ::std::move(from);
  }

  inline ClientData& operator=(const ClientData& from) {
    CopyFrom(from);
    return *this;
  }
  inline ClientData& operator=(ClientData&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return GetMetadataStatic().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return GetMetadataStatic().reflection;
  }
  static const ClientData& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const ClientData* internal_default_instance() {
    return reinterpret_cast<const ClientData*>(
               &_ClientData_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  friend void swap(ClientData& a, ClientData& b) {
    a.Swap(&b);
  }
  inline void Swap(ClientData* other) {
    if (other == this) return;
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  inline ClientData* New() const final {
    return CreateMaybeMessage<ClientData>(nullptr);
  }

  ClientData* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<ClientData>(arena);
  }
  void CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void CopyFrom(const ClientData& from);
  void MergeFrom(const ClientData& from);
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  #if GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  #else
  bool MergePartialFromCodedStream(
      ::PROTOBUF_NAMESPACE_ID::io::CodedInputStream* input) final;
  #endif  // GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
  void SerializeWithCachedSizes(
      ::PROTOBUF_NAMESPACE_ID::io::CodedOutputStream* output) const final;
  ::PROTOBUF_NAMESPACE_ID::uint8* InternalSerializeWithCachedSizesToArray(
      ::PROTOBUF_NAMESPACE_ID::uint8* target) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  inline void SharedCtor();
  inline void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(ClientData* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "Data.ClientData";
  }
  private:
  inline ::PROTOBUF_NAMESPACE_ID::Arena* GetArenaNoVirtual() const {
    return nullptr;
  }
  inline void* MaybeArenaPtr() const {
    return nullptr;
  }
  public:

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;
  private:
  static ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadataStatic() {
    ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&::descriptor_table_ClientData_2eproto);
    return ::descriptor_table_ClientData_2eproto.file_level_metadata[kIndexInFileMessages];
  }

  public:

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kUserNameFieldNumber = 2,
    kUserIdFieldNumber = 1,
  };
  // string user_name = 2;
  void clear_user_name();
  const std::string& user_name() const;
  void set_user_name(const std::string& value);
  void set_user_name(std::string&& value);
  void set_user_name(const char* value);
  void set_user_name(const char* value, size_t size);
  std::string* mutable_user_name();
  std::string* release_user_name();
  void set_allocated_user_name(std::string* user_name);

  // int32 user_id = 1;
  void clear_user_id();
  ::PROTOBUF_NAMESPACE_ID::int32 user_id() const;
  void set_user_id(::PROTOBUF_NAMESPACE_ID::int32 value);

  // @@protoc_insertion_point(class_scope:Data.ClientData)
 private:
  class _Internal;

  ::PROTOBUF_NAMESPACE_ID::internal::InternalMetadataWithArena _internal_metadata_;
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr user_name_;
  ::PROTOBUF_NAMESPACE_ID::int32 user_id_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_ClientData_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// ClientData

// int32 user_id = 1;
inline void ClientData::clear_user_id() {
  user_id_ = 0;
}
inline ::PROTOBUF_NAMESPACE_ID::int32 ClientData::user_id() const {
  // @@protoc_insertion_point(field_get:Data.ClientData.user_id)
  return user_id_;
}
inline void ClientData::set_user_id(::PROTOBUF_NAMESPACE_ID::int32 value) {
  
  user_id_ = value;
  // @@protoc_insertion_point(field_set:Data.ClientData.user_id)
}

// string user_name = 2;
inline void ClientData::clear_user_name() {
  user_name_.ClearToEmptyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline const std::string& ClientData::user_name() const {
  // @@protoc_insertion_point(field_get:Data.ClientData.user_name)
  return user_name_.GetNoArena();
}
inline void ClientData::set_user_name(const std::string& value) {
  
  user_name_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:Data.ClientData.user_name)
}
inline void ClientData::set_user_name(std::string&& value) {
  
  user_name_.SetNoArena(
    &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:Data.ClientData.user_name)
}
inline void ClientData::set_user_name(const char* value) {
  GOOGLE_DCHECK(value != nullptr);
  
  user_name_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:Data.ClientData.user_name)
}
inline void ClientData::set_user_name(const char* value, size_t size) {
  
  user_name_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:Data.ClientData.user_name)
}
inline std::string* ClientData::mutable_user_name() {
  
  // @@protoc_insertion_point(field_mutable:Data.ClientData.user_name)
  return user_name_.MutableNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline std::string* ClientData::release_user_name() {
  // @@protoc_insertion_point(field_release:Data.ClientData.user_name)
  
  return user_name_.ReleaseNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline void ClientData::set_allocated_user_name(std::string* user_name) {
  if (user_name != nullptr) {
    
  } else {
    
  }
  user_name_.SetAllocatedNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), user_name);
  // @@protoc_insertion_point(field_set_allocated:Data.ClientData.user_name)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)

}  // namespace Data

// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_ClientData_2eproto
