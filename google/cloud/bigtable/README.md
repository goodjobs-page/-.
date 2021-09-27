# Google Cloud Bigtable

[![Documentation][doxygen-shield]][doxygen-link]

[doxygen-shield]: https://img.shields.io/badge/documentation-master-brightgreen.svg
[doxygen-link]: http://googleapis.github.io/google-cloud-cpp/
[quickstart-link]: http://googleapis.github.io/google-cloud-cpp/

This directory contains the implementation of the Google Cloud Bigtable C++
client.

## Status

This library support Google Cloud Bigtable at the
[Beta](../README.md#versioning) quality level.

## Documentation

Full documentation, including a [quick start guide][quickstart-link]
is available [online][doxygen-link].

## Release Notes

### v0.9.x - TBD

### v0.8.x - 2019-04

* **Breaking change**: `Table::BulkApply` now returns a
  `std::vector<FailedMutation>` instead of throwing an exception.
* In the future we will remove all the `google::cloud::bigtable::noex::*`
  classes. We are moving the implementation to `google::cloud::bigtable::*`.
* Continuing to implement more async APIs (Note: These are not yet stable):
  * InstanceAdmin::AsyncDeleteInstance
  * Table::AsyncCheckAndMutateRow
  * TableAdmin::AsyncDeleteTable
  * TableAdmin::AsyncModifyColumnFamilies
* BulkMutator now returns more specific errors instead of generic UNKNOWN.
* Improved install instructions, which are now tested with our CI builds.
* CMake-config files now work without `pkg-config`.
* Removed the googleapis submodule. The build system now automatically
  downloads all deps.
* No longer throw exceptions from `ClientOptions`.

### v0.7.x - 2019-03

* **Breaking change**: Return `StatusOr<>` from `TableAdmin` and `InstanceAdmin`
  operations to signal errors.
* Add streaming to `(Async)BulkMutator`.
* Implement a helper class (`MutationBatcher`) to automatically batch and manage
  outstanding bulk mutations.
* Add `bigtable::Cell` constructors without labels argument.
* Implementation of `RowSet` example using discontinuous keys.
* `List{Instances,Clusters}` return `failed_locations`.
* First version of async `Apply` batching.
* Keep `Apply` callbacks in `MutationData`.

### v0.6.x - 2019-02

* Moved repo organization from GoogleCloudPlatform -> googleapis.
* Implemented several more async functions.
* **Breaking change**: Started migrating functions to `StatusOr` and away from
  throwing exceptions.
* Several fixes to bulk mutator (#1880)
* Disabled `make install` for external projects.
* `Row` now has a move constructor.
* Increased default message length limit.
* Now testing build with libc++ on Linux.
* Fixed some bugs found by Coverity scans.

### v0.5.x - 2019-01

* Restore support for gcc-4.8.
* @remyabel cleaned up some hard-coded zone names in the examples.
* More experimental asynchronous APIs, including AsyncReadRows. Note that we
  expect to change all these experimental APIs as described in
  [#1543](https://github.com/googleapis/google-cloud-cpp/issues/1543).
* @remyabel contributed changes to disable the unit and integration tests. This
  can be useful for package maintainers.
* New Bigtable filter wrapper that accepts a single column.
* **Breaking Change**: remove the `as_proto_move()` memnber functions in favor
  of `as_proto() &&`. With the latter newer compilers will warn if the object
  is used after the destructive operation.

### v0.4.x - 2018-12

* More experimental asynchronous APIs, note that we expect to change all these
  experimental APIs as described in
  [#1543](https://github.com/googleapis/google-cloud-cpp/issues/1543).
* Most of the admin operations now have asynchronous APIs.
* All asynchronous APIs in `noex::*` return an object through which applications
  can request cancellation of pending requests.
* Prototype asynchronous APIs returning a `google::cloud::future<T>`,
  applications can attach callbacks and/or block on a
  `google::cloud::future<T>`.

### v0.3.0 - 2018-11

* Include an example that illustrates how to use OpenCensus and the Cloud
  Bigtable C++ client library.
* Experimental asynchronous APIs.
* Several cleanups around dependency management with CMake.
* Jason Zaman contributed improvements and fixes to support soversion numbers
  with CMake.
* Lots of improvements to the code coverage in the examples and tests.
* Fixed multiple documentation issues, including a much better landing page
  in the Doxygen documentation.

### v0.2.0 - 2018-08

* First Beta release.
* Completed instance admin APIs.
* Completed documentation and examples.
* The API is considered stable, we do not expect any changes before 1.0

### v0.1.0 - 2018-03

* This release implements all the APIs for table and data manipulation in Cloud
  Bigtable.
* This release does not implement APIs to manipulate instances, please use the
  Google Cloud Bigtable
  [command line tool](https://cloud.google.com/bigtable/docs/go/cbt-overview)
  or any of the other programming language APIs instead.
* Only synchronous (blocking) APIs are implemented, asynchronous APIs are in
  our roadmap.
