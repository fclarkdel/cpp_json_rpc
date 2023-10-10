# Specification

## 1. Definitions

> 1. The key words **MUST**, **MUST NOT**, **REQUIRED**, **SHALL**, **SHALL
     NOT**, **SHOULD**, **SHOULD NOT**, **RECOMMENDED**,  **MAY**, and
     **OPTIONAL** in this document are to be interpreted as described in
     _RFC 2119_.
> 1. **Service** refers to any external resource
     accessible by a URL which exposes an API
     conformant to the _JSON-RPC 2.0 Specification_.
> 1. **Proxy** refers to the interface provided by this library to a **service**.
> 1. **Request** refers to either a request object or notification object
     as specified in sections 4 and 4.1 of the _JSON-RPC 2.0 Specification_.
> 1. **Response** refers to the response object
     as specified in section 5 of the _JSON-RPC 2.0 Specification_

## 2. Functional requirements

> 1. **MUST** be able to specify a **proxy** to a **service** with a URL.
> 1. **MUST** be able to specify connection protocol properties.
> 1. **MUST** be able to specify a **request** that can be stored and then later sent to a **service**.
> 1. **MUST** be able to send a **request** to a **service** and asynchronously receive the corresponding **response**.
> 1. **MUST** be able to explicitly utilize **batching** to send multiple **requests** and asynchronously receive their
     corresponding **responses**.

## 3. Non-functional requirements

> 1. **MUST** ensure thread safety for all interactions with a **service**.
> 1. **MUST** ensure that when **batching** is explicitly used by the user, all contained **requests** are sent in one
     network transfer.
> 1. **MUST** send **requests** to a **service**, whether singular or **batched**, in the order they are received by the
     **proxy**.